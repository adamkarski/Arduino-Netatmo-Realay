
var qrcode_=document.querySelector(".qr-code");
$(".qr-code").hide();




function generateQR(user_input){

  // Clear any existing QR code
  qrcode_.innerHTML = "";

var qrcode = new QRCode(qrcode_, {
    text: user_input,
    width: 256, //128
    height: 256,
    colorDark : "#000000",
    colorLight : "#ffffff",
    correctLevel : QRCode.CorrectLevel.H
});


// Make sure the QR code is visible
$(".qr-code").show();
/*
let ipc = document.createElement("p");
ipc.innerText = user_input;
document.querySelector(".qr-code").appendChild(ipc);


let close_qr = document.createElement("a");
close_qr.innerText = "+";
close_qr.classList.add("qr-close", "ring-8", "ring-white", "ring-opacity-40");
document.querySelector(".qr-code").appendChild(close_qr);


$("a.a_qrcode, .qr-code .qr-close").on("click", function(){
  $(".qr-code").toggle(400);
});
 */

}
