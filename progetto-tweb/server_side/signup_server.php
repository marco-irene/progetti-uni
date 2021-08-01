<?php
//File utilizzato da registration.js per effettuare la registrazione
include 'server_config.php';

$username = strip_tags(htmlspecialchars(addslashes($_POST['username'])));
$password = strip_tags(htmlspecialchars(addslashes($_POST['password'])));
$email = strip_tags(htmlspecialchars(addslashes($_POST['email'])));

//espressioni regolari
$usernameValidation = "/^[a-zA-Z][a-zA-Z0-9_]{3,15}$/";
$emailValidation = "/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9]+(\.[a-z]{2,4})$/";
$passwordValidation = "/^[a-zA-Z0-9]{7,15}$/";


//Validazione input form
if(empty($username) || empty($email) || empty($password)) {

    echo "
  <div id='alert_fail'>
  <b> &times; Compila tutti i campi! </b>
  </div>
  ";
    $conn = null;
    exit();

} else {
    if(!preg_match($usernameValidation, $username)){
        echo "
    <div id='alert_fail'>
    <b> &times; Username non valido!</b>
    </div>
    ";
        $conn = null;
        exit();
    }
    if(!preg_match($emailValidation, $email)){
        echo "
    <div id='alert_fail'>
    <b> &times; E-mail non valida!</b>
    </div>
    ";
        $conn = null;
        exit();
    }
    if((strlen($password) < 4 || strlen($password) > 16) || !preg_match($passwordValidation, $password) ){
        echo "
    <div id='alert_fail'>
    <b> &times; Password non valida!</b>
    </div>
    ";
        $conn = null;
        exit();
    }
}

//Controlliamo se l'username è già presente nel db
try{
    $quoteusername = $conn->quote($username);
    $sql = "SELECT username
  FROM users
  WHERE username = $quoteusername";

    $check_query = $conn->query($sql);
    $count_username = $check_query->fetchAll();
    if(sizeof($count_username) > 0){
        echo "
    <div id ='alert_fail'>
    <b> &times; L'username scelto è già presente nel nostro sistema. Scegline un altro e riprova. </b>
    </div>
    ";
        $conn = null;
        exit();


    } else { //creiamo record in tabella utente con i dati appena inseriti


        $passwordmd5=md5($password);
        $sql = "INSERT INTO users (username, password, email)
    VALUES (?, ?, ?)";

        $run_query = $conn->prepare($sql)->execute([$username, $passwordmd5, $email]);

        $conn = null;
        exit();
    }
}catch(PDOException $ex){
    echo $ex->getMessage();
}
