/* * * * * * validatore per checkout * * * * * */
const btn  = document.getElementById("check-out");
const firstName  = document.getElementById("firstName");
const lastName  = document.getElementById("lastName");
const addr  = document.getElementById("address");
const cc_name  = document.getElementById("cc-name");
const cc_num = document.getElementById("cc-number");
const cvv = document.getElementById("cc-cvv");
const cc_exp = document.getElementById("cc-expiration");

const addressCheck = /^(corso|via)+\s[a-zA-Z]+\s\d+$/;
const ccNumCheck = /^[0-9]{16}$/;
const cvvCheck = /^[0-9]{3}$/;
const ccExpCheck =/^\d{2}\/\d{2}$/;

btn.addEventListener('click', (e) => {
    e.preventDefault();
    check_inputs();
});


function check_inputs() {

    if (firstName.value.trim() === "" || firstName.value.trim().search(/\d/)!==-1) {
        setError(firstName);
    }else {
        setSuccess(firstName);
    }

    if (lastName.value.trim() === "" || lastName.value.trim().search(/\d/)!==-1) {
        setError(lastName);
    }else {
        setSuccess(lastName);
    }

    if (cc_name.value.trim() === "" || cc_name.value.trim().search(/\d/)!==-1) {
        setError(cc_name);
    }else{
        setSuccess(cc_name);
    }

    if (addr.value.trim() === "") {
        setError(addr);
    }else if (addressCheck.test(addr.value.trim())) {
        setSuccess(addr);
    }else{
        setError(addr);
    }

    if (cc_num.value.trim() === "") {
        setError(cc_num);
    }else if(ccNumCheck.test(cc_num.value.trim())){
        setSuccess(cc_num);
    }else{
        setError(cc_num);
    }

    if (cvv.value.trim() === "") {
        setError(cvv);
    }else if(cvvCheck.test(cvv.value.trim())){
        setSuccess(cvv);
    }else{
        setError(cvv);
    }

    if (cc_exp.value.trim() === "") {
        setError(cc_exp);
    }else if(ccExpCheck.test(cc_exp.value.trim())){
        setSuccess(cc_exp);
    }else{
        setError(cc_exp);
    }
}

function checkUser(name) {
    if (name.value.trim() === "" || name.value.trim().search(/\d/)!==-1) {
        setError(name);
    }else {
        setSuccess(name);
    }
}

function check_address_test() {
    if (addr.value.trim() === "") {
        setError(addr);
    }else if (addressCheck.test(addr.value.trim())) {
        setSuccess(addr);
    }else{
        setError(addr);
    }
}

function  check_cc_num_test() {
    if (cc_num.value.trim() === "") {
        setError(cc_num);
    }else if(ccNumCheck.test(cc_num.value.trim())){
        setSuccess(cc_num);
    }else{
        setError(cc_num);
    }
}
function  check_cvv_test() {
    if (cvv.value.trim() === "") {
        setError(cvv);
    }else if(cvvCheck.test(cvv.value.trim())){
        setSuccess(cvv);
    }else{
        setError(cvv);
    }
}

function  check_cc_exp() {
    if (cc_exp.value.trim() === "") {
        setError(cc_exp);
    }else if(ccExpCheck.test(cc_exp.value.trim())){
        setSuccess(cc_exp);
    }else{
        setError(cc_exp);
    }
}

function setSuccess(obj){
    $(obj).next().css('display', 'none');
    $(obj).removeClass("error");
    obj.classList.add("success");
}

function setError(obj){
    $(obj).next().css('display', 'contents');
    $(obj).removeClass("success")
    obj.classList.add("error");

}

firstName.addEventListener('blur', function () {
    checkUser(firstName);
}, false);

lastName.addEventListener('blur', function () {
    checkUser(lastName);
}, false);

cc_name.addEventListener('blur', function () {
    checkUser(cc_name);
}, false);

addr.addEventListener("blur", check_address_test,false);
cc_num.addEventListener("blur", check_cc_num_test,false);
cvv.addEventListener("blur", check_cvv_test,false);
cc_exp.addEventListener("blur", check_cc_exp,false);