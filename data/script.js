let yellowBlinkInterval = null;
let car = document.getElementById("car");
let carPosition = -150;
let carSpeed = 6; 
let carMoving = true; 

function updateCarPosition() {
    if (carMoving) {
        carPosition += carSpeed; 

        if (carPosition > window.innerWidth) {
        car.style.display = 'none'; 
        carPosition = -300; 
        car.style.left = carPosition + "px";

        setTimeout(() => {
            car.style.display = 'block'; 
        }, 10); 
        } else {
        car.style.left = carPosition + "px"; 
        }
    }
    requestAnimationFrame(updateCarPosition); 
}
      
updateCarPosition();

function switchLight(color) {
    let red = document.getElementById('red_light');
    let yellow = document.getElementById('yellow_light');
    let green = document.getElementById('green_light');

    if (color === 'red' && green.classList.contains('on')) {
        green.classList.remove('on');
        green.classList.add('off');
        fetch("/green/led/off");
        
        yellow.classList.add('on');
        fetch("/yellow/led/on"); 
        carSpeed = 3;
        carMoving = true;

        setTimeout(() => {
        yellow.classList.remove('on');
        yellow.classList.add('off');
        fetch("/yellow/led/off"); 
        
        red.classList.add('on'); 
        fetch("/red/led/on");
        carMoving = false;
        }, 1000);

    } else if (color === 'green' && red.classList.contains('on')) {
        yellow.classList.add('on');
        fetch("/yellow/led/on");

        setTimeout(() => {
        yellow.classList.remove('on');
        yellow.classList.add('off');
        fetch("/yellow/led/off"); 

        red.classList.remove('on');
        red.classList.add('off');
        fetch("/red/led/off"); 
        
        green.classList.add('on');
        fetch("/green/led/on");
        carSpeed = 6;
        carMoving = true;
        }, 1000);

    } else {
        red.classList.remove('on');
        yellow.classList.remove('on');
        green.classList.remove('on');

        red.classList.add('off');
        yellow.classList.add('off');
        green.classList.add('off');

        if (yellowBlinkInterval) {
            clearInterval(yellowBlinkInterval);
            yellowBlinkInterval = null;
        }

        if (color === 'yellow') {
            red.classList.remove('on');
            red.classList.add('off');
            fetch("/red/led/off");

            green.classList.remove('on');
            green.classList.add('off');
            fetch("/green/led/off");

            yellowBlinkInterval = setInterval(() => {
            if (yellow.classList.contains('on')) {
                yellow.classList.remove('on');
                yellow.classList.add('off');
                fetch("/yellow/led/off");
            } else {
                yellow.classList.remove('off');
                yellow.classList.add('on');
                fetch("/yellow/led/on");
                carSpeed = 3;  
                carMoving = true;
            }
            }, 500);

        } else {  

            if (yellowBlinkInterval) {
                clearInterval(yellowBlinkInterval);
                yellowBlinkInterval = null;
            }

            if (color === 'red') {
            
                yellow.classList.remove('on');
                yellow.classList.add('off');
                fetch("/yellow/led/off");

                green.classList.remove('on');
                green.classList.add('off');
                fetch("/green/led/off");

                red.classList.remove('off');
                red.classList.add('on');
                fetch("/red/led/on");
                carMoving = false;

            } else if (color === 'green') {
                yellow.classList.remove('on');
                yellow.classList.add('off');
                fetch("/yellow/led/off");

                red.classList.remove('on');
                red.classList.add('off');
                fetch("/red/led/off");

                green.classList.remove('off');
                green.classList.add('on');
                fetch("/green/led/on");
                carSpeed = 6;
                carMoving = true;
            }
        }
    }
}