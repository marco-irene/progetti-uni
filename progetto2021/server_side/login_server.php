<?php
//File utilizzato da registration.js per effettuare il login
if(isset($_POST["userBool"])){
    include 'server_config.php';

    $username = (htmlspecialchars(addslashes($_POST["username"])));
    $password =(htmlspecialchars(addslashes(md5($_POST["password"])))) ;

    $usernameValidation = "/^[a-zA-Z][a-zA-Z0-9_]{3,15}$/";
    $passwordValidation = "/^[a-zA-Z0-9]{7,15}$/";

    if(empty($username) || empty($password) ){
        echo (2);
        $conn = null;
        exit();
    }

    try{
        $quoteusername = $conn->quote($username);
        $quotepassword = $conn->quote($password);

        //controlliamo se username e password sono corretti
        $sql = "SELECT username, password
						FROM users
						WHERE username = $quoteusername AND password = $quotepassword";

        $run_query = $conn->query($sql);
        $res = $run_query->fetchAll();

        if(sizeof($res) == 1){
            if(isset($_SESSION)){
                session_regenerate_id();
            }

            $_SESSION['utente'] = $res[0]['username'];

            echo(1);//caso successo
            $conn = null;
            exit();

        } else{
            echo(2);//caso fallimento
            $conn = null;
            exit();
        }
    }catch(Exception $e){
        echo $e;
    }
}
