
<?php
require_once("../server_side/server_config.php");
if (!isset($_SESSION)) {         //se non esiste una sessione la inizio
    session_start();
    if (isset($_SESSION["utente"])) {
        unset($_SESSION["utente"]);    //se esiste la sessione con il nome cancello il nome
    }
}

session_destroy();               //distruggo i dati della sessione
//session_regenerate_id(TRUE);     //sostituisco la sessione corrente con una nuova mantenendo le informazioni(x garantire maggiore sicurezza)
session_start();                 //inizio una sessione
header("Location:index.php", "Logout successful.");
