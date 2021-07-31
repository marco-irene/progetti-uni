<?php
//File di configurazione del database usato da login e signup

if(!isset($_SESSION)){
    session_start();
}

try {
    $hostname = "localhost";
    $dbname = "iceland_experience_db";
    $user = "root";
    $pass = "";
    $conn = new PDO ("mysql:host=$hostname;dbname=$dbname", $user, $pass);
} catch (PDOException $e) {
    //debug_to_console("Errore db_connection: " . $e->getMessage());
    echo "Errore db_connection: " . $e->getMessage();
    die();
}
