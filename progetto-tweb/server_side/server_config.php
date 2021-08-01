<?php
if (!isset($_SESSION)) {
    session_start();
}
include 'db_config.php';
include 'db_manager.php';



//FUNZIONE DI REDIRECT ALL'INDEX SE NON ESISTE UN UTENTE LOGGATO
function redirect($url, $flash_message = NULL)
{
    if ($flash_message) {
        $_SESSION["flash"] = $flash_message;
    }
    header("Location: $url");
    die;
}

function search_review()
{
    $rows = rows_db("SELECT user,date,text FROM reviews");
    if($rows->rowCount()){
        foreach ($rows as $row){
            echo "
			<div class=\"service-item\" id=\"card-review\" >
                <div>
                    <img src='../img/people.png'>
                    <h2>" . $row['user'] . "</h2>
                    <p>" . $row['date'] . "</p>
                </div>
                <p>" . $row['text'] . "</p>
            </div>";
        }
    }else{
        echo "
            <p>Non sono presenti recensioni.</p>
        ";
    }
}

function write_rev($user, $review)
{
    $check=insert_review($user,$review);

    if ($check) {
        echo (1);
        exit();
    } else {
        echo (2);
        exit();
    }
}

function print_list_products()
{
    $query = "SELECT * FROM products";
    $rows = rows_db($query);
    $num=1;
    if ($rows->rowCount()) {
        foreach ($rows as $row) {
            ?>
            <form class="service-item" id="<?php echo "item".$num++; ?>" >
                <h2><?php echo $row['name'] ?></h2>
                <input type="hidden" name="title" id="title" value="<?php echo $row['name']?>">
                <p><?php echo $row['description'] ?></p>
                <p class="price"><?php echo $row['price'] ?><span class="fa fa-eur"></p>
                <details>
                    <summary>PRENOTA</summary>
                    <div class="form-group">
                        <div id="col-1">
                            <span class="form-label">Data:</span>
                            <input class="form-control" name="date" type="date" id="data">
                        </div>
                        <div id="col-2">
                            <span>Persone:</span>
                            <select class="form-control" name="quantity" id="quantity">
                                <option>1</option>
                                <option>2</option>
                                <option>3</option>
                                <option>4</option>
                            </select>
                        </div>
                        <div id="col-3">
                            <button class="add-to-cart">Aggiungi al carrello</button>
                        </div>
                    </div>
                </details>
            </form>
            <?php
        }
    }
}

function print_cart(){

    $user_id = get_user_id($_SESSION['utente']);

    $query ="SELECT DISTINCT C.id, P.price,C.quantity,C.date,P.name FROM cart_item AS C JOIN products AS P WHERE C.product_id = P.id AND C.user_id = $user_id";
    $rows = rows_db($query);

    if ($rows->rowCount()) {
        foreach ($rows as $row) {
            $total=$row['price'] * $row['quantity'];
    ?>
        <li class="list-group-item d-flex justify-content-between lh-condensed p-4">
            <div class="row w-100">
                <div class="col-lg-4 col-6">
                    <h6 class="my-0"><?php echo $row['name']?></h6>
                </div>
                <div class="col-lg-2 col-6">
                    <span class="text-muted"><?php echo $row['price']?></span>
                </div>
                <div class="col-lg-4 col-6">
                    <form method="post">
                        <div class="cart-buttons btn-group" role="group">
                            <button name="minus" type="submit" class="btn btn-sm btn-primary">-</button>
                            <span class="text-muted"><?php echo $row['quantity']?></span>
                            <button name="plus" type="submit" class="btn btn-sm btn-primary">+</button>
                            <input type="hidden" name="id" value="<?php echo $row['id']?>"/>
                            <input type="hidden" name="price" value="<?php echo $row['price']?>"/>
                        </div>
                    </form>
                </div>
                <div class="col-lg-2 col-6">
                    <strong class="text-muted"><?php echo$total?></strong>
                </div>
            </div>
        </li>
    <?php
        }
    }else {
        ?>
        <li class="list-group-item d-flex justify-content-between lh-condensed p-4">
            <div class="row w-100">
                <div class="col-lg-7 col-12">
                    <h6 class="my-0">Non sono presenti elementi nel carrello esplora le nostre offerte..</h6>
                </div>
                <div class="col-lg-3 col-8"></div>
                <div class="col-lg-2 col-1">
                    <button class="btn btn-primary btn-block"><a href="../php/explore.php">Esplora</button>
                </div>
            </div>
        </li>
        <?php
    }
}
function total_(){

    $user_id = get_user_id($_SESSION['utente']);

    $query ="SELECT DISTINCT C.price FROM cart_item AS C JOIN users AS U WHERE C.user_id = $user_id";
    $rows = rows_db($query);
    $res = [
        'total' => 0,
        'num_elem' => 0
    ];
    if($rows->rowCount()){
        foreach ($rows as $row){
            $res['total'] = $row['price'] + $res['total'];
            $res['num_elem']++;
        }
        ?>
<li class="card-total list-group-item d-flex justify-content-between p-4">

    <div class="row w-100">
        <div class="col-lg-4 col-6">
            <span>Totale (EUR):</span>
        </div>

        <div class="col-lg-7 lg-screen"></div>
        <div class="col-lg-2 col-6">
            <strong><?php echo  $res['total']?></strong>
        </div>
    </div>
        <form method="post" action="../php/checkout.php">
    <button name="check" type="submit" class="btn btn-primary btn-block">Procedi all'ordine</button>
            <input type="hidden" name="total" value="<?php echo $res['total']?>"/>

        </form>
    <?php
    }
}
function add_cart($id,$single_price){

    $num_person = get_quantity($id);

    if($num_person<4) {
        $db = db_connect();
        $stmt = $db->prepare("UPDATE cart_item SET quantity=quantity+1, price=$single_price+price WHERE id = $id");
        $stmt->execute();
    }else{
        echo "
    <div id ='alert_fail'>
    <b> &times; Puoi prenotare solo per 4 persone. </b>
    </div>
    ";
    }
}

function remove_cart($id,$single_price){

    $num_person = get_quantity($id);

    if($num_person>1) {
        $db = db_connect();
        $stmt = $db->prepare("UPDATE cart_item SET quantity=quantity-1, price=price-$single_price WHERE id = $id");
        $stmt->execute();
    }else {
        $db = db_connect();
        $stmt = $db->prepare("DELETE FROM cart_item WHERE id = $id");
        $stmt->execute();
    }
}

function summary_checkout($user){

    $user_id = get_user_id($user);

    $query ="SELECT DISTINCT C.id, P.price,C.quantity,C.date,P.name FROM cart_item AS C JOIN products AS P WHERE C.product_id = P.id AND C.user_id = $user_id";
    $rows = rows_db($query);

    if ($rows->rowCount()) {
        foreach ($rows as $row) {
            $total = $row['price'] * $row['quantity'];
            ?>
            <li class="list-group-item d-flex justify-content-between lh-condensed">
                <div>
                    <h6 class="my-0"><?php echo  $row['name']?></h6>
                </div>
                <span class="text-muted"><?php echo  $row['price']?></span>
            </li>
            <?php
        }
    }
}