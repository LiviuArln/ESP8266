name := """g8Scaffold form"""
organization := "com.excelsioriot"

version := "1.0-SNAPSHOT"

lazy val root = (project in file(".")).enablePlugins(PlayScala)

scalaVersion := "2.12.3"

libraryDependencies += guice
libraryDependencies += "org.scalatestplus.play" %% "scalatestplus-play" % "3.1.2" % Test
libraryDependencies += "org.fusesource.mqtt-client" % "mqtt-client" % "1.5"
//libraryDependencies += "net.sigusr" %% "scala-mqtt-client" % "0.6.0"

// Adds additional packages into Twirl
//TwirlKeys.templateImports += "com.excelsioriot.controllers._"

// Adds additional packages into conf/routes
// play.sbt.routes.RoutesKeys.routesImport += "com.excelsioriot.binders._"
