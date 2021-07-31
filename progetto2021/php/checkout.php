<!DOCTYPE html>
<html>
<head>
    <title>Checkout</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-eOJMYsd53ii+scO/bJGFsiCZc+5NDVN2yr8+0RDqr0Ql0h+rP48ckxlpbzKgwra6" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="../css/style.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
    <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
    <script src="../js/checkout.js"></script>
</head>

<body class="bg-light">
<script type="text/javascript" src="../js/logout.js"></script>

<?php
include("../server_side/server_config.php");
include("../html/header.php");
?>
<?php
if (!isset($_SESSION["utente"])) {
    redirect("index.php", "x Login necessario per accedere alle pagine del sito");

}
$user = $_SESSION['utente'];
?>
<section id="main-page">
    <div class="main-container" id="container">
        <div class="row"  style="margin-top: 130px; background-color: white; padding: 20px;">

            <div class="col-md-4 order-md-2 mb-4">
                <h4 class="d-flex justify-content-between align-items-center mb-3">
                    <span class="text-muted">Riepilogo</span>
                    <span class="badge badge-secondary badge-pill">3</span>
                </h4>
                <ul class="list-group mb-3">
                    <?php summary_checkout($user); ?>
                    <li class="list-group-item d-flex justify-content-between">
                        <span>Total: (EUR)</span>
                        <strong><?php echo $_POST['total']?></strong>
                    </li>
                </ul>

                <form class="card p-2">
                    <div class="input-group">
                        <input type="text" class="form-control" placeholder="Promo code">
                        <div class="input-group-append">
                            <button type="submit" class="btn btn-secondary">Inserisci</button>
                        </div>
                    </div>
                </form>
            </div>
            <div class="col-md-8 order-md-1">
                <h4 class="mb-3">Checkout</h4>
                <form class="needs-validation" method="" action="">
                    <div class="row">
                        <div class="col-md-6 mb-3">
                            <label for="firstName">Nome</label>
                            <input type="text" class="form-control" name="firstName" id="firstName" placeholder="" value="" required>
                            <div class="invalid-feedback" id="feed">
                                Nome non valido.
                            </div>
                        </div>
                        <div class="col-md-6 mb-3">
                            <label for="lastName">Cognome</label>
                            <input type="text" class="form-control" name="lastName" id="lastName" placeholder="" value="" required>
                            <div class="invalid-feedback" id="feed">
                                Cognome non valido.
                            </div>
                        </div>
                    </div>

                    <div class="mb-3">
                        <label for="address">Indirizzo di fatturazione</label>
                        <input type="text" class="form-control" id="address" name="address" placeholder="via/corso example 1234" required>
                        <div class="invalid-feedback">
                            Per favore inserisci un indirizzo valido.
                        </div>
                    </div>

                    <hr class="mb-4">

                    <h4 class="mb-3">Pagamento</h4>

                    <div class="d-block my-3">
                        <div class="custom-control custom-radio">
                            <input id="credit" name="paymentMethod" type="radio" class="custom-control-input" checked required>
                            <label class="custom-control-label" for="credit">Carta di credito</label>
                        </div>
                        <div class="custom-control custom-radio">
                            <input id="debit" name="paymentMethod" type="radio" class="custom-control-input" required>
                            <label class="custom-control-label" for="debit">Carta di debito</label>
                        </div>
                        <div class="custom-control custom-radio">
                            <input id="paypal" name="paymentMethod" type="radio" class="custom-control-input" required>
                            <label class="custom-control-label" for="paypal">Paypal</label>
                        </div>
                    </div>
                    <div class="row">
                        <div class="col-md-6 mb-3">
                            <label for="cc-name">Nome</label>
                            <input type="text" class="form-control" id="cc-name" name="cc-name" placeholder="" required>
                            <small class="text-muted">Nome intestatario della carta</small>
                            <div class="invalid-feedback">
                                Name on card is required
                            </div>
                        </div>
                        <div class="col-md-6 mb-3">
                            <label for="cc-number">Numero carta di credito</label>
                            <input type="text" class="form-control" id="cc-number" name="cc-number" placeholder="" required>
                            <div class="invalid-feedback">
                                Numero della carta di credito richiesto.
                            </div>
                        </div>
                    </div>
                    <div class="row">
                        <div class="col-md-3 mb-3">
                            <label for="cc-expiration">Scadenza</label>
                            <input type="text" class="form-control" id="cc-expiration" name="cc-expiration" placeholder="" required>
                            <div class="invalid-feedback">
                                Data di scadaenza richiesto.
                            </div>
                        </div>
                        <div class="col-md-3 mb-3">
                            <label for="cc-expiration">CVV</label>
                            <input type="text" class="form-control" id="cc-cvv" name="cc-cvv" placeholder="" required>
                            <div class="invalid-feedback">
                                Codice di sicurezza richiesto.
                            </div>
                        </div>
                    </div>
                    <hr class="mb-4">
                    <button type="submit" class="btn btn-primary btn-lg btn-block" id="check-out">Acquista</button>
                </form>
            </div>
        </div>

    </div>
</section>
<?php include("../html/footer.html");?>
<script src="../js/checkout_validator.js"></script>
</body>