<?php
//file utilizzato per validare le recensioni
include("server_config.php");
$textvalidation="/^[a-zA-Z][a-zA-Z\s,.!]*$/";

if (isset($_POST["txt"]) && ($_POST["txt"])!= "") {
    $user = ($_SESSION["utente"]);
    $review =(htmlspecialchars(addslashes($_POST["txt"])));
    if(preg_match($textvalidation, $review)){
        write_rev($user,$review);
    }
    else
        exit();
}