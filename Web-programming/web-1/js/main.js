import {drawGraph, drawPoint} from "./graph.js";

const elsTyper = document.querySelectorAll("span");
const rand = (min, max) => Math.floor(Math.random() * (max - min + 1) + min);

var form = document.querySelector('.validateForm');
var submitBut = form.querySelector('.submitButton');
var xVal = form.querySelectorAll('.x');
var yVal = form.querySelector('.y');
var rVal = form.querySelectorAll('.r');
function getNum(checkboxOrRadio){
    for(var i = 0; i < checkboxOrRadio.length; i++){
        var num;
        if (checkboxOrRadio[i].checked) {
            return checkboxOrRadio[i].value;
        }
    }
}
function validateCheckbox(checkboxes){
    var counter = 0;
    for(var i = 0; i < checkboxes.length; i++){
        if (checkboxes[i].checked) counter++; 
    }
    return true;
}
function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
}

function removeErrors() {
    var errors = form.querySelectorAll('em')      
    for (var i = 0; i < errors.length; i++) {
        errors[i].remove()
    }
  }

function validateInput(num, min, max){
    if(num.value){
        num.value = num.value.replace(',','.');
        if(isNumeric(num.value) && num.value >= min && num.value <= max){
            return true;
        }
        else{
            generateError(num,'wrong number format');
        }
    }
    else{
        generateError(num,'field is blank');
    }
}
function generateError(parent,text){
    $("<em></em>").insertBefore($(parent));
    $(parent.parentElement).find("em").animate({opacity: "show", top: $(parent).offset().top-80}, "slow");
    $(parent.parentElement).find("em").text(text);
}
function validateRadio(radios){
    var parent = radios[0].parentElement;
    for(var i = 0 ; i < radios.length; i++){
        if(radios[i].checked) return true;
    }
    generateError(parent,'field is blank');
    return false;

}
function validateFields(){
    return  validateRadio(xVal) & validateInput(yVal,-5,5) & validateRadio(rVal);
}
$(document).ready(function(){
    $.ajax({
        url: 'php/load.php',
        method: "GET",
        dataType: "html",
        success: function(data){
          console.log(data);
          $("#answersTable > tbody").html(data);
        },
        error: function(error){
          console.log(error);	
        },
    })
    drawGraph();
    const typer = (el) => {
        const text = el.dataset.typer;
        const tot = text.length;
        let ch = 0;
      
        (function typeIt() {
          if (ch > tot){
            el.removeAttribute('data-typer');
            return;
          }
          el.innerHTML = text.substring(0, ch++);
          setTimeout(typeIt, rand(10, 20));
        }());
    };
    elsTyper.forEach(typer);
})

$("#form").on('submit', function(event) {
    event.preventDefault();
    var x = getNum(xVal);
    var r = getNum(rVal);
    console.log("xVal: ", xVal);
    console.log("yVal: ", yVal.value);
    console.log("rVal: ", r);
    removeErrors();
    if (!validateFields()){
        console.log("get canceled")
        return
    }
    console.log("data sending...");
    $.ajax({
        url: 'php/server.php',
        method: "GET",
        data: $(this).serialize() + "&timezone=" + new Date().getTimezoneOffset(),
        dataType: "html",
  
        success: function(data){
          console.log(data);
          $(".submitButton").attr("disabled", false);	
          $("#answersTable > tbody").html(data);
          var canvas = document.getElementById("graph");
          var ctx = canvas.getContext("2d");
          ctx.clearRect(0, 0, canvas.width, canvas.height);
          var xt = x*100/r+150;
          var yt =  (-yVal.value)*100/r+150;
          drawPoint(xt,yt, r);
          console.log(xt);
          console.log(yt);
        },
        error: function(error){
          console.log(error);
          $(".submitButton").attr("disabled", false);	
        },
    })
});

$(".resetButton").on('click', function(){
    $.ajax({
        url: 'php/reset.php',
        method: "GET",
        dataType: "html",
        success: function(data){
          console.log(data);
          $("#answersTable > tbody").html(data);
        },
        error: function(error){
          console.log(error);	
        },
    })
})
