/* * * * * * Ajax per checkout * * * * * */
$(document).ready(function () {

    $(".btn-primary").click(function () {
        $.ajax({
            url: "../server_side/checkout_server.php",
            method: "POST",
            data: $(".needs-validation").serialize(),
            success: function (res) { //res = echo
                if (res !== '') {
                    $(".row").addClass("res-check-out").html(res);
                }
            }
        })
    })

});