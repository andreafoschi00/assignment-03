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

	private static final int MAX_SIZE = 1; // Just use one object --> it has the updated values.
	private static final String SERIAL_PORT = ""; // --> ARDUINO SERIAL PORT GOES HERE
	private static final int SERIAL_BAUD_RATE = 0; // --> ARDUINO BAUD RATE GOES HERE
    private final int port;
    private final LinkedList<DataStruct> values;
    private CommChannel channel;

    public DataService(int port) {
        values = new LinkedList<>();
        this.port = port;
        try {
            this.channel = new SerialCommChannel(SERIAL_PORT, SERIAL_BAUD_RATE);
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void start() {
        Router router = Router.router(vertx);
        router.route().handler(BodyHandler.create());
        // endpoints
        router.post("/api/data").handler(this::handleAddNewData);
        router.get("/api/data").handler(this::handleGetData);

        vertx
                .createHttpServer()
                .requestHandler(router)
                .listen(port);

        log("Service ready.");
    }
    
    // POST /api/data
    private void handleAddNewData(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        JsonObject res = routingContext.getBodyAsJson();
        if (res == null) {
            sendError(400, response);
        } else {
            int intensity = res.getInteger("intensity");
            int temperature = res.getInteger("temperature");
            String state = res.getString("state");

            // All the components must know the system passed in ALARM mode
            if (temperature == 5) { 
                state = "alarm";
            }

            values.addFirst(new DataStructImpl(intensity, temperature, state));
            if (values.size() > MAX_SIZE) {
                values.removeLast();
            }

            response.setStatusCode(200).end();

            channel.sendMsg(temperature + "," + intensity + "," + state); // --> to the Arduino
            log("<-sensorboard: " + "t:" + temperature + " i:" + intensity + " s:" + state);
            log("->controller: " + temperature + "," + intensity + "," + state);
            log("->dashboard: updated");
            log("->app: updated");
       }
    }

    // GET /api/data
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
