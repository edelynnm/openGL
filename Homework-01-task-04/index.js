// const triangle = document.querySelector(".triangle");

const area = document.querySelector("#area");

let height = 50;

function drawTriangle(div, marginBottom) { // creates 1 triangle
  const canvas = document.createElement("canvas");
  const ctx = canvas.getContext("2d");

  const start = 5;

  canvas.id = "triangle";
  canvas.height = height + start;
  canvas.width = height + start;
  canvas.style.marginBottom = `${marginBottom}px`;

  ctx.beginPath();
  ctx.moveTo(start, start);
  ctx.lineTo(height / 2, height);
  ctx.lineTo(height, start);
  ctx.closePath();

  ctx.lineWidth = 2;
  ctx.strokeStyle = "#000";
  ctx.stroke();

  div.appendChild(canvas);
}

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

function createCol() {
  const col = document.createElement("div");

  col.id = "col";

  for(let i = 0; i< 1; i++) {
  let marginBottom = getRandomInt(15)
  drawTriangle(col, marginBottom*10 +i);
  }

  area.appendChild(col);
}


function draw() {
  for(let i = 0; i< 5; i++) {

  let marginBottom = getRandomInt(15)
  createCol()
//   drawTriangle(area,marginBottom*10 +i);
  }
}

let secondsPassed=0;
let oldTimeStamp=0;
let fps = 0;

const fpsDiv = document.querySelector('#fps')
// const context = fpsDiv.getContext("2d")

function gameLoop(timeStamp) {
 
    // Calculate the number of seconds passed since the last frame
    secondsPassed = (timeStamp - oldTimeStamp) / 1000;
    oldTimeStamp = timeStamp;

    // Calculate fps
    fps = Math.round(1 / secondsPassed);
    fpsDiv.innerHTML = "FPS: " + fps;

    draw()

    window.requestAnimationFrame(gameLoop)
}

function init() {
  window.requestAnimationFrame(gameLoop)
}

window.onload = init
