package controllers

import javax.inject._
import play.api._
import play.api.mvc._
import org.fusesource.mqtt.client._


@Singleton
class HomeController @Inject()(cc: ControllerComponents) extends AbstractController(cc) {
  import collection.JavaConversions._
  var lastMessage = "11111000100101010000010110000001111111111001"

  def index() = Action { implicit request: Request[AnyContent] =>
    Ok(views.html.index())
  }

  def messageToDevice() = Action { implicit request: Request[AnyContent] =>
    MQTTComm.send(lastMessage)
    lastMessage = MQTTComm.recieve
    Ok(views.html.message(lastMessage))
  }
}

object MQTTComm {
  var server:MQTT = new MQTT
  server.setHost("localhost", 1883)
  server.setClientId("webClient")

  val connection = server.blockingConnection
  
  def recieve = {
    connection.subscribe(Array(new Topic("webTopic", QoS.AT_MOST_ONCE)))
    val message = connection.receive
    val result = new String(message.getPayload)
    message.ack
    result
  }

  def send(message:String) = {
    if(!connection.isConnected)  connection.connect
    connection.publish("thingyTopic", message.getBytes, QoS.AT_MOST_ONCE, false)
  }
}