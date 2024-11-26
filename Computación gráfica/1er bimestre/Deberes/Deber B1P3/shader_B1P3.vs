#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float time; // Variable uniforme para el tiempo

void main()
{
    gl_Position = vec4(aPos, 1.0);

    // Modifica el color dinámicamente usando el tiempo
    float red = abs(sin(time));      // Oscila entre 0 y 1
    float green = abs(cos(time));    // Oscila entre 0 y 1
    float blue = abs(sin(time * 0.5)); // Oscila más lentamente

    if(red + aColor.r > 1){
        red = red + aColor.r - 1;
    }else{
        red = red + aColor.r;
    }

    if(green + aColor.g > 1){
        green = green + aColor.g - 1;
    }else{
        green = green + aColor.g;
    }

    if(blue + aColor.b > 1){
        blue = blue + aColor.b - 1;
    }else{
        blue = blue + aColor.b;
    }

    ourColor = vec3(red, green, blue); // Calcula un color dinámico
}