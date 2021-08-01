<?php
//File utilizzato per completare acquisto
include 'server_config.php';


$firstName = strip_tags(htmlspecialchars(addslashes($_POST['firstName'])));
$lastName = strip_tags(htmlspecialchars(addslashes($_POST['lastName'])));
$address = strip_tags(htmlspecialchars(addslashes($_POST['address'])));
$cc_name = strip_tags(htmlspecialchars(addslashes($_POST['cc-name'])));
$cc_num = strip_tags(htmlspecialchars(addslashes($_POST['cc-number'])));
$cc_cvv = strip_tags(htmlspecialchars(addslashes($_POST['cc-cvv'])));
$cc_exp = strip_tags(htmlspecialchars(addslashes($_POST['cc-expiration'])));

//espressioni regolari
$nameValidation = "/^[a-zA-Z]+\s+[a-zA-Z]+$/";
$addrValidation = "/^(corso|via)+\s[a-zA-Z]+\s\d+$/";
$ccNumValidation = "/^[0-9]{16}$/";
$cvvValidation = "/^[0-9]{3}$/";
$ccExpValidation = "/^\d{2}\/\d{2}$/";

$user=$_SESSION['utente'];
$db = db_connect();
$user = $db->quote($user);
$stmt = $db->prepare("SELECT id,email FROM users WHERE username = $user");
$stmt->execute();
foreach ($stmt as $row){
    $email=$row['email'];
    $id = $row['id'];
}

//Validazione input form
if( (empty($firstName) || empty($lastName) || empty($address) || empty($cc_name) || empty($cc_num) || empty($cc_cvv) || empty($cc_exp)) && (!preg_match($nameValidation, $firstName) || !preg_match($nameValidation, $lastName) || !preg_match($nameValidation, $cc_name) || !preg_match($addrValidation, $address)
        || !preg_match($ccNumValidation, $cc_num) || !preg_match($cvvValidation, $cc_cvv) || !preg_match($ccExpValidation, $cc_exp))) {

    $conn = null;
    exit();

}else{
    $db = db_connect();
    $stmt = $db->prepare("DELETE FROM cart_item WHERE user_id = $id");
    $stmt->execute();
    echo" <b>&#10003; Acquisto fatto con successo!
                        Abbiamo inviato un'email con le istruzione all'indirizzo: " . $email . "</b>";

    $conn = null;
    exit();
}

