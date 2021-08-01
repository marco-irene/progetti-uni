<!-- Marco Irene
       Matricola: 812146
       Index page del sito -->

<header>
    <nav class="navbar">
        <div class="openMenu"><i class="fa fa-bars"></i> </div>
        <ul class="mainMenu">
            <li class="effect-menu"><a href="../php/index.php">Home</a></li>
            <li class="effect-menu"><a href="../php/#about">Chi siamo</a></li>
            <li class="effect-menu"><a href="../php/#contact">Contatti</a></li>
            <li class="effect-menu"><a href="../php/reviews.php">Recensioni</a></li>
            <li><a href="../php/cart.php"><span id="cart" class="fa fa-shopping-cart"></span>Carrello</a></li>
            <div class="closeMenu"><i class="fa fa-times"></i></div>
        </ul>
    </nav>
    <?php
    if (!isset($_SESSION)) {
        session_start();
    }
    ?>
    <div class="log">
        <?php if (!isset($_SESSION["utente"])) {
        ?>
        <a href="../php/login.php"><button>LOG IN</button></a>
        <?php } else { ?>
            <a id="user" href="#"><?php echo ($_SESSION['utente']); ?></a>
            <a id="exit" href="../php/logout.php"> LOG OUT</a>
        <?php } ?>
    </div>
</header>

<!--* * * * * * script per navbar , menu e logout * * * * * *-->
<script src="../js/script_nav.js"></script>
<script src="../js/menu.js"></script>
<script type="text/javascript" src="../js/logout.js"></script>
