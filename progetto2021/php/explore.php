<!-- Marco Irene
       Matricola: 812146
       products page del sito -->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * viewport,css e icons * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">
    <link rel="shortcut icon" type="image/png" href="../img/iceland.png">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * jquery e ajax  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * script aggiung al carrello  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="../js/add_cart.js"></script>

    <title>Explore</title>
</head>

<body>

<?php include("../html/header.php");
    include ("../server_side/server_config.php");
if (!isset($_SESSION["utente"])) {
    redirect("index.php", "Login necessario per accedere alle pagine del sito");
}
?>

<section id="services">
    <div id="banner-top">
        <div class="title">
            <h1>Vivi la tua esperienza</h1>
            <h4>Prenota l'avventura più adatta a te</h4>
        </div>
    </div>
    <div class="services container">
        <div class="service-bottom">
            <div id="cart_msg"></div>
            <?php
            print_list_products();
            ?>
        </div>
    </div>
</section>

<?php include("../html/footer.html");?>

</body>
</html>