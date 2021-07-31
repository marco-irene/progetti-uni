/* * * * * * Ajax per effettuare logout * * * * * */
$(document).ready(function () {
  $("#exit").click(function () {
    $.ajax({
      url: "../php/logout.php",
    });
  });
});
