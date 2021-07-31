/* * * * * * ** * * * * * * * * * * * Script per inviare le recensioni * * * * * * * * * * * * * * * * * * * * * * * * * ** * * * * * */
$(document).ready(function () {
    $("#send_rev").click(function () {
        $("#form_rev").hide();
        $.ajax({
            url: "../server_side/write_review.php",
            method: "POST",
            data: $("form").serialize(),
            success: function (res) {
                if (res == 1) {
                    rev_ok();
                    $.ajax({
                        url: "../php/print_reviews.php",
                        method: "POST",
                    });
                } else {
                    rev_no();
                } //res = echo
            },
        });
    });
});
function rev_ok() {
    var resul = document.getElementById("rev_msg");
    temp =
        "<div id = 'alert_rev'> <b> &#10003; Recensione Inserita Correttamente</b> </div>";
    resul.innerHTML = temp;
}
function rev_no() {
    var resul = document.getElementById("rev_msg");
    temp =
        "<div id = 'alert_rev'> <b> &times; Recensione Non Inserita</b> </div>";
    resul.innerHTML = temp;
}
