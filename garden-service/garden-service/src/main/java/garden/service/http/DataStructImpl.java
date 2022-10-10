package garden.service.http;

public class DataStructImpl implements DataStruct {

	private int intensity;
	private int temperature;
	private String state;
	
	public DataStructImpl(final int intensity, final int temperature, final String state) {
		this.intensity = intensity;
		this.temperature = temperature;
		this.state = state;
	}
	
	@Override
	public int getLightIntensity() {
		return this.intensity;
	}

	@Override
	public int getTemperature() {
		return this.temperature;
	}

	@Override
	public String getState() {
		return this.state;
	}

}
