<!-- Marco Irene
       Matricola: 812146
       reviews page del sito -->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * viewport,css e icons * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * jquery e ajax  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * script per le recensioni  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="../js/write_reviews.js"></script>

    <title>Reviews</title>
</head>

<body>

<?php
include("../server_side/server_config.php");
include("../html/header.php");?>
<?php
if (!isset($_SESSION["utente"])) {
    redirect("index.php", "x Login necessario per accedere alle pagine del sito");
} ?>

<section id="services">
    <div id="banner-top">
        <div class="title">
            <h1>Dicono di noi</h1>
            <h4>Facci sapere come è andata</h4>
        </div>
    </div>
    <div class="services container">
        <div class="service-bottom">
            <?php
            search_review();
            ?>
            <div class="write-review">
                <form id="form-rev" value="" name="form_rev" action="" method="">
                    <textarea id="txt" name="txt" maxlength="100" rows="4" cols="50" placeholder="Inserisci qui la tua recensione"></textarea>
                    <input id="send_rev" name="send_rev" type="submit" value="Invia" />
                </form>
                <div id='rev_msg'></div>
            </div>
        </div>
    </div>
</section>

<?php include("../html/footer.html");?>

</body>
</html>