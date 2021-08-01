<!-- Marco Irene
       Matricola: 812146
       cart page del sito -->
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Carrello</title>

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * viewport, bootstrap, css e icons * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="shortcut icon" type="image/png" href="../img/iceland.png">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-eOJMYsd53ii+scO/bJGFsiCZc+5NDVN2yr8+0RDqr0Ql0h+rP48ckxlpbzKgwra6" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * jquery e ajax  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>

</head>

<body>
<?php
include("../server_side/server_config.php");
include("../html/header.php");

if (!isset($_SESSION["utente"])) {
    redirect("index.php", "x Login necessario per accedere alle pagine del sito");

}
?>
<section id="main-page">
    <div class="main-container" id="container">
        <div class="col-12">
            <h4 class="d-flex justify-content-between align-items-center mb-3">
                <span class="text-primary text-white">Carrello</span>
            </h4>
            <ul class="list-group mb-3">
            <?php
            if (isset($_POST['minus'])) {
                $cart_item_id=htmlspecialchars(trim($_POST['id']));
                $price=htmlspecialchars(trim($_POST['price']));
                remove_cart($cart_item_id,$price);
                unset($_POST['minus']);
            }
            if (isset($_POST['plus'])) {
                $cart_item_id=htmlspecialchars(trim($_POST['id']));
                $price=htmlspecialchars(trim($_POST['price']));
                add_cart($cart_item_id,$price);
                unset($_POST['plus']);
            }
            print_cart();
            total_();
            ?>
            </ul>
        </div>
    </div>
</section>

<?php include("../html/footer.html");?>

</body>
</html>
