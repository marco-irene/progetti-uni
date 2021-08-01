<?php
//funzioni richimate per operazioni sul db
function db_connect() {
    try {
        $hostname = "localhost";
        $dbname = "iceland_experience_db";
        $user = "root";
        $pass = "";
        return new PDO ("mysql:host=$hostname;dbname=$dbname", $user, $pass);
    } catch (PDOException $e) {
        //debug_to_console("Errore db_connection: " . $e->getMessage());
        echo "Errore db_connection: " . $e->getMessage();
        die();
    }
}

function rows_db($query) { //return rows
    $dsn = 'mysql:dbname=iceland_experience_db;host=localhost';
    try {
        $db = new PDO($dsn, 'root', '');
        $rows = $db->query($query);
        return $rows;
    } catch (PDOException $ex) {
        ?>
        <p>Sorry, a database error occurred.</p>
        <?php
        return NULL;
    }
}

function get_user_id($user){
    $db = db_connect();
    $user = $db->quote($user);
    $stmt = $db->prepare("SELECT id FROM users WHERE username = $user");
    $stmt->execute();
    foreach ($stmt as $row){
        $user_id=$row['id'];
    }
    return $user_id;
}

function insert_review($user,$review){
    $db = db_connect();
    $user = $db->quote($user);
    $date = $db->quote(date('Y-m-d'));
    $review = $db->quote($review);
    $query = "INSERT INTO reviews (user, date, text) VALUES ($user,$date,$review)";
    $check = $db->prepare($query);
    return $check->execute();
}

function get_quantity($id){
    $conn = db_connect();
    $stmt = $conn->prepare("SELECT quantity FROM cart_item WHERE id = $id");
    $stmt->execute();
    foreach ($stmt as $row){
        $num_person=$row['quantity'];
    }
    return $num_person;
}