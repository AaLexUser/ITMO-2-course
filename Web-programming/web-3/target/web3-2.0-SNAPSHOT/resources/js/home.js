import {Graph} from "./graph.js";
let graph = new Graph(document.getElementById("graph"));
let table = [];
let xHidden = document.getElementById("form:x");
let yInput = document.getElementById("form:y");
let submitButton = document.getElementById("form:submit-btn");
let xLabel = document.getElementById("form:x-label");
let selectedRs = [];
const xLim = {min:-5,max: 3};
const yLim = {min:-3,max:3};
(function () {

    window.selectedX = selectedX;
    function selectedX(value) {
        if ((value) != null) {
            console.log(xLabel);
            console.log(xHidden);
            console.log(value);
            xLabel.innerText = "Selected value: " + value;
            xHidden.value = value;
        }
    }
    window.selectedR = selectedR;
    function selectedR(value) {
        console.log(value);
        if (!isNaN(value)) {
            selectedRs.push(value);
        }
        console.log(selectedRs);
    }
    window.deselectedR = deselectedR;
    function deselectedR(value) {
        console.log(value);
        let index = selectedRs.indexOf(value);
        if (index !== -1) {
            selectedRs.splice(index, 1);
        }
        console.log(selectedRs);
    }

})();

function  redrawGraph(){
    $('#result_table_data> tr ').each(function (i, element){
        let x = $(this).find("td>span.x").text().trim();
        let y = $(this).find(".y").text().trim();
        let r = $(this).find(".r").text().trim();
        let hit = $(this).find(".hit").text().trim() === 'Попадание';
        table[i]=[x, y, r, hit];
    });
    graph.draw();
    if(table.length>0){
        for(let i = 0; i < table.length; i++){
            graph.drawPoint(table[i][0], table[i][1], table[i][2], table[i][3]);
        }
    }
}


$(document).ready(function() {
    redrawGraph();
    const r = $(".r__panel .r");
    r.map(function () {
        let input = $(this).find("input");
        if(input[0].checked){
            let label = $(this).find("span.ui-chkbox-label")[0]
            console.log(label);
            selectedRs.push(label.textContent);
        }
    });
});

graph.canvas.addEventListener('click', (event) => {
    console.log("r:" + selectedRs)
    console.log(selectedRs.length)
    if (selectedRs.length!==0){
        let x = graph.getMousePosition(event).x;
        let y = graph.getMousePosition(event).y;
        let w = graph.canvas.width;
        let h = graph.canvas.height;
        for (let i in selectedRs){
            let r = selectedRs[i];
            let scaleX = (x - w / 2) * r / (1 / 3 * w);
            let scaleY = -(y - h / 2) * r / (1 / 3 * h);
            if (scaleX >= xLim.max || scaleX <= xLim.min) {
                alert("Error: X value:" + scaleX + " – is incorrect!");
                return;
            }
            if (scaleY >= yLim.max || scaleY <= yLim.min) {
                alert("Error: Y value:" + scaleY + " – is incorrect!");
                return;
            }
            graph.drawPoint(scaleX, scaleY, r, true)
            console.log("scaleX:" + scaleX);
            console.log("scaleY:" + scaleY);
            console.log("data sending...");
            xHidden.value = scaleX;
            xLabel.innerText = "Selected value: " + scaleX;
            yInput.value = scaleY;
            submitButton.click();
        }
    } else {
        alert("Error: R field is incorrect!")
    }
});