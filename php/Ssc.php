<?php
class Ssc{
    public function sendSensorsStatus($arg){ //no necesita ningun parámetro realmente.
        $sql = "SELECT * FROM sensorsStatus";
        $array = $this->Conexion->connection->query($sql);
        if(!$this->Conexion->connection->query($sql) === true){
            echo "\n- Error en la petición -> " . $this->connection_error . "\n";
        }
        $response = array();
        while($row = $array->fetch_assoc()){
            array_push($response,$row);
        }
        // $response = $this->Conexion->convertToBase64($response);
        //return json_encode($response,true);
        return $response;
    }
    
    public function updateSensorsStatus($arg){
        for ($i=0; $i < sizeof($arg); $i++) { 
            $sensorName = $arg[$i]['sensorName'];
            $state = $arg[$i]['state'];

            $sql = "UPDATE sensorsStatus SET state = '$state' WHERE sensorName = '$sensorName'";
            if(!$this->Conexion->connection->query($sql)){
                echo 'petición fallida -> ' . $this->connection_error;
                return 0;
            }
        }
        return 1;
    }

    public function addTemperatureHumidity($arg){
        $temperrature = $arg['temperature'];
        $humidity = $arg['humidity'];

        $sql = "INSERT INTO ssc_history_temperature_humidity (humidity, temperature)values($humidity, $temperrature)";
        if(!$this->Conexion->connection->query($sql)){
            echo 'petición fallida -> ' . $this->connection_error;
            return 0;
        }
        return 1;
    }

    public function sendTemperatureAndHumidityLogs($arg){
        $sql = "SELECT * FROM ssc_history_temperature_humidity";
        $array = $this->Conexion->connection->query($sql);
        if(!$this->Conexion->connection->query($sql) === true){
            echo "\n- Error en la petición -> " . $this->connection_error . "\n";
        }
        $response = array();
        while($row = $array->fetch_assoc()){
            array_push($response,$row);
        }
        return $response;
    }
}
?>
// 
