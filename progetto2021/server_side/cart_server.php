<?php
//File utilizzato da registration.js per effettuare la registrazione
include 'server_config.php';

$quantity = strip_tags(htmlspecialchars(addslashes($_POST['quantity'])));
$title = $_POST['title'];
$event_date =date('Y-m-d',strtotime ($_POST['date']));
$today = date("Y-m-d");
$today_stamp = strtotime($today);
$event_stamp = strtotime ($_POST['date']);
$user = $_SESSION["utente"];

try{
    if($today_stamp > $event_stamp){
        echo "
    <div id ='alert_fail'>
    <b> &times; Data errata. </b>
    </div>
    ";
    }else {
        $rows = $conn->prepare("SELECT id, price FROM products WHERE name =:title");
        $rows->execute(['title' => $title]);

        foreach ($rows as $row) {
            $product_id = $row['id'];
            $price = $row['price'] * $quantity;
        }


        $quoteuser = $conn->quote($user);
        $rows = $conn->prepare("SELECT id FROM users WHERE username = $quoteuser");
        $rows->execute();

        foreach ($rows as $row) {
            $user_id = $row['id'];
        }

        $query = "INSERT INTO cart_item (user_id, product_id, price, quantity, date)
    VALUES (?, ?, ?, ?, ?)";

        $run_query = $conn->prepare($query)->execute([$user_id, $product_id, $price, $quantity, $event_date]);
        $conn = null;
        exit();
    }
}catch(PDOException $ex){
    echo $ex->getMessage();
}