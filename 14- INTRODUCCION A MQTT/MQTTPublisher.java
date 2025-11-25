import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttException;

public class MQTTPublisher {
    public static void main(String[] args) {

        String topic = "test/tema";
        String content = "Mensaje con QoS 1 y retenido";
        int qos = 1;
        String broker = "tcp://localhost:1883";
        String clientId = "JavaPublisher";

        try {
            MqttClient client = new MqttClient(broker, clientId);
            client.connect();

            MqttMessage message = new MqttMessage(content.getBytes());
            message.setQos(qos);
            message.setRetained(true);

            client.publish(topic, message);
            System.out.println("Mensaje publicado");

            client.disconnect();
            System.out.println("Desconectado");

        } catch(MqttException me) {
            System.out.println("Reason " + me.getReasonCode());
            System.out.println("Mensaje " + me.getMessage());
            System.out.println("Localización " + me.getLocalizedMessage());
            System.out.println("Causa " + me.getCause());
            System.out.println("Excepción " + me);
            me.printStackTrace();
        }
    }
}