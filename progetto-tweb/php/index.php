<!-- Marco Irene
       Matricola: 812146
       Index page del sito -->

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Home</title>
    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * viewport,css e icons * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">
    <link rel="shortcut icon" type="image/png" href="../img/iceland.png" />

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>

</head>

<body>
<?php
include("../server_side/server_config.php");
include("../html/header.php");?>

<section id="main-page">
    <div class="main-container" id="container">
        <div>
            <?php if (isset($_SESSION["flash"])) { ?>
                <div id="flash"><?= $_SESSION["flash"] ?></div>
                <?php unset($_SESSION["flash"]);
            } ?>
            <h1>Iceland</h1>
            <h1>Experience</h1>
            <a href="explore.php"><button id="explore" type="button">Esplora</button></a>
        </div>
    </div>
</section>

<section id="about">
    <div class="about-container" id="container">
        <div class="col-left item2">
            <div class="about-img">
                <img src="../img/carousel1.jpg" alt="img">
            </div>
        </div>
        <div class="col-right item1">
            <h1 class="section-title">ABOUT <span>US</span></h1>
            <p>L'Islanda è famosa per i suoi meravigliosi paesaggi ma anche per la sua vasta offerta di tour avventurosi,
                per questo potrebbe essere difficile scegliere da dove iniziare! Spesso ci chiedono dei consigli su cosa fare e dove andare,
                ecco allora la nostra lista delle cose migliori da fare in Islanda!</p>
        </div>
    </div>
</section>

<section id="contact">
    <div class="contact-container" id="container">
        <div><h1 class="section-title">CONTACT <span>INFO</span></h1></div>
        <div class="contact-items">
            <div class="contact-item">
                <div class="icon"><span class="fa fa-phone"></span></div>
                <div class="contact-info">
                    <h2>Phone</h2>
                    <h3>+354 123 456 789</h3>
                </div>
            </div>
            <div class="contact-item">
                <div class="icon"><span class="fa fa-envelope"></span></div>
                <div class="contact-info">
                    <h2>Email</h2>
                    <h3>iceland_exp@gmail.com</h3>
                </div>
            </div>
            <div class="contact-item">
                <div class="icon"><span class="fa fa-map-marker"></span></div>
                <div class="contact-info">
                    <h2>Address</h2>
                    <h3>Laugavegur 72, 101 Reykjavík, Islanda</h3>
                </div>
            </div>
        </div>
    </div>
</section>

<?php include("../html/footer.html");?>

</body>
</html>