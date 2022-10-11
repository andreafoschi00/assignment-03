package garden.service.http;

import java.util.LinkedList;

import garden.service.serial.CommChannel;
import garden.service.serial.SerialCommChannel;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import jssc.SerialPortException;

public class DataService extends AbstractVerticle {

	private static final int MAX_SIZE = 10;
    private final int port;
    private final LinkedList<DataStruct> values;
    private CommChannel channel;

    public DataService(int port) {
        values = new LinkedList<>();
        this.port = port;
        try {
            this.channel = new SerialCommChannel("COM7", 115200);
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void start() {
        Router router = Router.router(vertx);
        router.route().handler(BodyHandler.create());
        router.post("/api/data").handler(this::handleAddNewData);
        router.get("/api/data").handler(this::handleGetData);

        vertx
                .createHttpServer()
                .requestHandler(router)
                .listen(port);

        log("Service ready.");
    }

    private void handleAddNewData(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        JsonObject res = routingContext.getBodyAsJson();
        if (res == null) {
            sendError(400, response);
        } else {
            int intensity = res.getInteger("intensity");
            int temperature = res.getInteger("temperature");
            String state = res.getString("state");

            if (temperature == 5) {
                state = "alarm";
            }

            values.addFirst(new DataStructImpl(intensity, temperature, state));
            if (values.size() > MAX_SIZE) {
                values.removeLast();
            }

            response.setStatusCode(200).end();

            channel.sendMsg(temperature + "," + intensity + "," + state);
            log("<-sensorboard: " + "t:" + temperature + " i:" + intensity + " s:" + state);
            log("->controller: " + temperature + "," + intensity + "," + state);
            log("->dashboard: updated");
       }
    }

    private void handleGetData(RoutingContext routingContext) {
        JsonArray arr = new JsonArray();
        for (DataStruct p : values) {
            JsonObject data = new JsonObject();
            data.put("intensity", p.getLightIntensity());
            data.put("temperature", p.getTemperature());
            data.put("state", p.getState());
            arr.add(data);
        }
        routingContext.response()
                .putHeader("content-type", "application/json")
                .end(arr.encodePrettily());
    }

    private void sendError(int statusCode, HttpServerResponse response) {
        response.setStatusCode(statusCode).end();
    }

    private void log(String msg) {
        System.out.println("[DATA SERVICE] " + msg);
    }

}
