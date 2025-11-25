import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttException;

public class MQTTSubscriber {

    public static void main(String[] args) {

        String topic = "test/tema";
        int qos = 1;
        String broker = "tcp://localhost:1883";
        String clientId = "JavaSubscriber";

        try {
            MqttClient client = new MqttClient(broker, clientId);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(false); // Mantener la sesión persistente

            client.setCallback(new MqttCallback() {

                @Override
                public void connectionLost(Throwable cause) {
                    System.out.println("Conexión perdida: " + cause.getMessage());
                }

                @Override
                public void messageArrived(String topic, MqttMessage message) throws Exception {
                    System.out.println("Mensaje recibido: " + new String(message.getPayload()) + " en el tema " + topic);
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    // No se utiliza en el suscriptor
                }
            });

            client.connect(connOpts);
            System.out.println("Conectado");

            client.subscribe(topic, qos);
            System.out.println("Suscrito al tema: " + topic);

            // Mantener el cliente en ejecución
            // Puedes utilizar un Thread.sleep() o mantener el programa corriendo de otra forma
            while (true) {
                // Mantener el hilo vivo
            }

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