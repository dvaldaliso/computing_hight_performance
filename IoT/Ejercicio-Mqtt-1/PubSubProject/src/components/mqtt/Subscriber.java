package components.mqtt;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import utils.MySimpleLogger;

public class Subscriber implements IMqttMessageListener {

    protected String subscriberId = null;

    public Subscriber(String subscriberId) {
        this.subscriberId = subscriberId;
    }

    
    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {

        String payload = new String(message.getPayload());
		
		MySimpleLogger.info(this.subscriberId, "-------------------------------------------------");
		MySimpleLogger.info(this.subscriberId, "| Topic:" + topic);
		MySimpleLogger.info(this.subscriberId, "| Message: " + payload);
		MySimpleLogger.info(this.subscriberId, "-------------------------------------------------");

        
    }
    
}
