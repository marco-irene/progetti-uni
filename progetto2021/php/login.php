<!-- Marco Irene
       Matricola: 812146
       Index page del sito -->

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Login</title>
    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * viewport,css e icons * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">
    <link rel="shortcut icon" type="image/png" href="../img/iceland.png" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * jquery e ajax  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>

    <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * Script per login e registrazione * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-->
    <script src="../js/registration.js"></script>

</head>
<body>

<?php include("../html/header.php");?>

    <section id="main-page">
        <div id="container">
            <div class="wrapper2">
                <form class="form" id="form-login">
                    <h1>LOG IN</h1>
                    <div class="form-inputs">
                        <label>User Name</label>
                        <input type="text" name="username"  id="username">
                    </div>
                    <div class="form-inputs">
                        <label>Password</label>
                        <input type="password" name="password"  id="password">
                    </div>
                    <div class="form-inputs">
                        <input type="submit" id="submit_login" name="" value="ACCEDI">
                    </div>
                    <div id="register">
                        <h4> Not a member?</h4>
                        <button id="reg-button"><a href="signup.php">REGISTER</a></button>
                    </div>
                    <div id="signup_msg"></div>
                </form>
            </div>
        </div>
    </section>

<?php include("../html/footer.html");?>

</body>
</html>