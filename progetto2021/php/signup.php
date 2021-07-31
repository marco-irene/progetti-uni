<!-- Marco Irene
       Matricola: 812146
       signup page del sito -->

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * viewport,css e icons * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">
    <link rel="shortcut icon" type="image/png" href="../img/iceland.png">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * jquery e ajax  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
    <script src="../js/registration.js"></script>
    <title>Signup</title>
</head>

<body>

<?php include("../html/header.php");?>

<section id="main-page">
    <div id="container">
        <div class="wrapper2">
            <form id="form-registration" class="form" method="post" action="../server_side/signup_server.php">
                <h1>Sign Up</h1>
                <div class="form-inputs">
                    <label>User Name</label>
                    <input type="text" name="username" placeholder="Username" id="username">
                    <span class="err" id="errUser"></span>
                </div>
                <div class="form-inputs">
                    <label>Password</label>
                    <input type="password" name="password" placeholder="Password" id="password">
                    <span class="err" id="errPass"></span>
                </div>
                <div class="form-inputs">
                    <label>Email</label>
                    <input type="text" name="email" placeholder="Email" id="email">
                    <span class="err" id="errEmail"></span>
                </div>
                <div class="form-inputs">
                    <input type="submit" id="submit_reg" name="" value="CREATE ACCOUNT">
                </div>
                <div id="signup_msg"></div>
            </form>
        </div>
        <div id="push"></div>
    </div>
</section>

<?php include("../html/footer.html");?>

<script src="../js/form_validator.js"></script>

</body>
</html>