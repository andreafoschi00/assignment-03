package garden.service;

import io.vertx.core.Vertx;
import garden.service.http.DataService;

public class GardenService {

	public static void main(String[] args) {
		Vertx vertx = Vertx.vertx();
        DataService service = new DataService(8080);
        vertx.deployVerticle(service);
	}

}
