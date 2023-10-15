import {drawGraph, drawPoint, getMousePosition, canvas} from "./graph.js";

let form = document.querySelector('.validateForm');
let xVal = form.querySelector('.x');
let yVal = form.querySelector('.y');
let rVal = form.querySelector('.r');
let table = [];

const xLim = {min:-5,max: 3};
const yLim = {min:-5,max:3};
const rLim = {min: 1,max: 4};

function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
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

function validateFields(){
    return  validateInput(xVal,-5,3) & validateInput(yVal,-5,3) & validateInput(rVal,1,4);
}
function validateField(input) {
    input.parentElement.querySelector('label').style.color  = '#0068ff';
    let err = input.parentElement.querySelectorAll('em');
    for (let i = 0; i < err.length; i++){
        err[0].remove();
    }
    if(input.classList.contains("x") || input.classList.contains("y")){
        validateInput(input, -5, 3);
    }
    else if (input.classList.contains("r")){
        validateInput(input, 1, 4);
    }

}

function generateError(parent,text){
    $("<em></em>").insertAfter($(parent));
    $(parent.parentElement).find("em").animate({opacity: "show", top: $(parent).offset().top-17}, "slow");
    $(parent.parentElement).find("em").text(text);
    let label = parent.parentElement.querySelector('label')
    label.style.color = '#ff0404'
}

function removeErrors() {
    let errors = form.querySelectorAll('em')
    for (let i = 0; i < errors.length; i++) {
        errors[i].remove()
    }
    let labels = form.querySelectorAll('label')
    for (let i = 0; i < labels.length; i++){
        labels[i].style.color = '#0068ff'
    }
}

form.addEventListener('change',function (event){
    const target = event.target; //reference to the object onto which the event was dispatched.
    console.log(target.classList.value)
    if (!target.classList.contains('text-field')){
        return;
    }
    validateField(target);
});

function  redrawGraph(){
    $('#table>tbody tr').each(function (i, element){
        let x = $(this).find(".x").text().trim();
        let y = $(this).find(".y").text().trim();
        let r = $(this).find(".r").text().trim();
        let hit = $(this).find(".hit").text().trim() === 'hit';
        table[i]=[x, y, r, hit];
    });
    drawGraph();
    if(table.length>0){
        for(let i = 0; i < table.length; i++){
            drawPoint(table[i][0], table[i][1], table[i][2], table[i][3]);
        }
    }
}

$(document).ready(function() {
    redrawGraph();
});
$('#form').on('submit', function(event) {
    event.preventDefault();
    console.log("x: ", xVal.value);
    console.log("y: ", yVal.value);
    console.log("r: ", rVal.value);
    removeErrors();
    if (!validateFields()){
        console.log("POST canceled")
        return
    }
    console.log("data sending...");
    $.ajax({
        url: './controller',
        method: "post",
        data:
            {
                "x": xVal.value,
                "y": yVal.value,
                "r": rVal.value,
                "timezone": new Date().getTimezoneOffset()
            },
        success: function(data){
            $(".submitButton").attr("disabled", false);
            window.location.replace("index.jsp");
            redrawGraph();
        },
        error: function(error){
            console.log(error);
            $(".validate_button").attr("disabled", false);
            window.location.replace("error.jsp");
        }
    });
});
$("#form").on("reset",function(e) {
    e.preventDefault();
    $.ajax({
        url: './controller',
        method: "post",
        data:
            {
                "clean": true
            },
        success: function(data){
            $(".resetButton").attr("disabled", false);
            window.location.replace("index.jsp");
            redrawGraph();
        },
        error: function(error){
            console.log(error);
            $(".validate_button").attr("disabled", false);
            window.location.replace("error.jsp");
        }
    });
});


canvas.addEventListener('click', (event) => {
    removeErrors();
    console.log("r:" + rVal.value)
    console.log(!isNaN(rVal.value))
    if (!isNaN(rVal.value)&&rVal.value<=rLim.max&&rVal.value>=rLim.min){
        let r = rVal.value;
        let x = getMousePosition(event).x;
        let y = getMousePosition(event).y;
        let w = canvas.width;
        let h = canvas.height;
        console.log(x, y);
        let scaleX = (x - w / 2) * r / (1 / 3 * w);
        let scaleY = -(y - h / 2) * r / (1 / 3 * h);
        if(scaleX>=xLim.max || scaleX<=xLim.min){
            alert("Error: X value:" + scaleX + " – is incorrect!");
            return;
        }
        if(scaleY>=yLim.max || scaleY<=yLim.min){
            alert("Error: Y value:" + scaleY + " – is incorrect!");
            return;
        }
        drawPoint(scaleX,scaleY, r ,true)
        console.log("scaleX:" + scaleX);
        console.log("scaleY:" + scaleY);
        console.log("data sending...");
        $.ajax({
            url: './controller',
            method: "post",
            data:
                {
                    "x": scaleX,
                    "y": scaleY,
                    "r": rVal.value,
                    "timezone": new Date().getTimezoneOffset()
                },
            success: function(data){
                window.location.replace("index.jsp");
                redrawGraph();
            },
            error: function(error){
                console.log(error);
                window.location.replace("error.jsp");
                console.log(error);
            }
        });
    } else {
        alert("Error: R field is incorrect!")
    }
});