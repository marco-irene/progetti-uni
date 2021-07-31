/* * * * * * Ajax per login e registrazione * * * * * */

$(document).ready(function () {
  //REGISTRAZIONE
  $("#submit_reg").click(function (event) {
    event.preventDefault();
    $.ajax({
      url: "../server_side/signup_server.php",
      method: "POST",
      data: $("form").serialize(),
      success: function (res) { //res = echo
        if (res =='') {
          var data = "<div id = 'alert_success'> <p> <b>&#10003; Registrazione effettuata con successo!</b> </p> </div> \
                      <div id = 'redirect'> <p> Tra pochi secondi sarai reindirizzato automaticamente alla pagina di login...<br> altrimenti clicca <a href='../php/login.php'>QUI</a> </p> </div>";
          $('#form-registration').html(data);
          var delay = 3000;
          setTimeout(function () { window.location = "../php/login.php"; }, delay);
        } else {
          $("#signup_msg").html(res);
        }
      }
    })
  });

  //LOGIN
  $("#submit_login").click(function (event) {
    event.preventDefault();
    var username = $("#username").val();
    var password = $("#password").val();
    $.ajax({
      url: "../server_side/login_server.php",
      method: "POST",
      data: { userBool: 1, username: username, password: password },
      success: function (res) {
        if (res == 1) {
          var data = "<div id = 'alert_success'> <p> <b>&#10003; Login effettuato con successo!</b> </p> </div>";
          $('#form-login').html(data);
          var delay = 2000;
          setTimeout(function () { window.location = "../php/index.php"; }, delay);
        } else {
          loginError();
        }
      },

    })
  })
});

function loginError() {
  var resul = document.getElementById("signup_msg");
  var temp = "<div id = 'alert_fail'> <b> &times; Username o password errati! </b> </div>";
  resul.innerHTML = temp;
}

