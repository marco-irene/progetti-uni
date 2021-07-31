/* * * * * * Ajax aggiungere al carrello * * * * * */
$(document).ready(function () {
const item = document.querySelectorAll(".service-item");

    for(let i=0; i<item.length; i++){
        $(item[i]).find("button").click(function (e) {
            e.preventDefault();
            let currentItem=$(this).parents(".service-item");
            let title=$(currentItem).find("h2").html();
            let date=$(currentItem).find("#data").val();
            let quantity=$(currentItem).find("#quantity").val();
            $.ajax({
                url: "../server_side/cart_server.php",
                method: "POST",
                data:  {title: title, date: date, quantity: quantity},
                success: function (res) {
                    if(res==''){
                        $("#cart_msg").css("visibility", "visible").html("<b> &#10003; Aggiunto al carrello</b>");
                        setTimeout(function(){ $("#cart_msg").css("visibility", "hidden"); }, 2000);
                    }else{
                        $("#cart_msg").css("visibility", "visible").html(res);
                        setTimeout(function(){ $("#cart_msg").css("visibility", "hidden"); }, 2000);
                    }
                }
            })
        })
    }
});



