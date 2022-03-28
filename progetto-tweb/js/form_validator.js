/* * * * * * * * * * * * * * * * * * * * * * * * * * * * js validator per la registrazione  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
const user  = document.getElementById("username");
const email = document.getElementById("email");
const pass  = document.getElementById("password");


const userCheck  = /^[a-zA-Z][a-zA-Z0-9_]{3,15}$/;
const passCheck  = /^[a-zA-Z0-9]{7,15}$/;
const emailCheck = /^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9]+(\.[a-z]{2,4})$/;
const charCheck=/^[a-zA-Z]/;



    function checkUser() {
        if(user.value.trim()===""){
            onError(user, "*campo vuoto");
        } else if(userCheck.test(user.value.trim())){
            onSuccess(user);
        }else if(!(charCheck.test(user.value.trim().charAt(0)))){
            onError(user,"*username deve iniziare con una lettera");
        }else if(user.value.trim().length < 4) {
            onError(user, "*username deve contenere almeno quattro caratteri");
        }else if(user.value.trim().length > 16) {
            onError(user, "*username troppo lungo");
        }
    }

    function checkPass() {
        if(pass.value.trim()===""){
            onError(pass, "*campo vuoto");
        } else
        if(passCheck.test(pass.value.trim())){
            onSuccess(pass);
        }else if(pass.value.trim().length < 8) {
            onError(pass, "*password deve contenere almeno otto caratteri");
        }else if(pass.value.trim().length > 16){
            onError(pass, "*password troppo lungo");
        }else{
            onError(pass, "*password può contenere solo numeri e lettere");
        }
    }

    function checkEmail() {
        if(email.value.trim()===""){
            onError(email, "*campo vuoto");
        } else
        if(emailCheck.test(email.value.trim())){
            onSuccess(email);
        }else{
            onError(email,"*formato e-mail non corretto");
        }
    }

function onSuccess(input){
    let parent=input.parentElement;
    let messageEle=parent.querySelector("span");
    messageEle.style.visibility="hidden";
    parent.classList.remove("error");
    parent.classList.add("success");
}
function onError(input,message){
    let parent=input.parentElement;
    let messageEle=parent.querySelector("span");
    messageEle.innerText=message;
    parent.classList.add("error");
    parent.classList.remove("success");
}

user.addEventListener('blur', checkUser, false);
pass.addEventListener('blur', checkPass, false);
email.addEventListener('blur', checkEmail, false);

