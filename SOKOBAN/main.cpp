#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

BITMAP *buffer;
BITMAP *muro;
BITMAP *pj;
BITMAP *box;
BITMAP *star;
BITMAP *nivel1;
BITMAP *nivel2;
BITMAP *nivel3;
BITMAP *presione;
BITMAP *teclas;
BITMAP *menu;
BITMAP *jugarl;
BITMAP *reglas;
BITMAP *salir;
BITMAP *logo;
BITMAP *copi;
BITMAP *instr;

BITMAP *a1;
BITMAP *a2;
BITMAP *a3;
BITMAP *a4;
BITMAP *a5;
BITMAP *a6;
BITMAP *a7;

BITMAP *b1;
BITMAP *b2;
BITMAP *b3;
BITMAP *b4;
BITMAP *b5;
BITMAP *b6;
BITMAP *b7;

MIDI *musica;
MIDI *mm;
MIDI *goal;
MIDI *death;
MIDI *good;
MIDI *msd;

int mapa[13][20];
int dir;
int px=12*30, py=10*30;
int nivel;

void jugar(int mov[3],char cadena[40]);
bool comprobar_ganar();
void dibujar_pj();
void mover_cajas();
bool detecta_perder();
void asignar_casillas();
void mostrar();
void dibujar_mapa(char cadena[40]);
void imprimir_controles();
void genera_mapa3();
void genera_mapa2();
void genera_mapa1();
void men(int op[1]);


int main() { // MENU

    int levelup = 0;
    int movmax;
    int mov[3]={0,0,0};
    int op[1];
    char cadena[40];
    int i=0;
    char lt;

	allegro_init();
	install_keyboard();

	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 880,600, 0, 0);



    //Inicializar Audio
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) { allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error); return 1; }
    //ajustar Volumen
    set_volume(220,220);



    musica = load_midi("midi/smoke.mid");
    mm = load_midi("midi/mm.mid");
    goal = load_midi("midi/goal.mid");
    death = load_midi("midi/death.mid");
    good = load_midi("midi/good.mid");
    msd = load_midi("midi/msd.mid");
    buffer = create_bitmap(880,600);
    muro = load_bitmap("img/roca1.bmp",NULL);
    pj = load_bitmap("img/pj.bmp",NULL);
    box = load_bitmap("img/box.bmp",NULL);
    star = load_bitmap("img/star.bmp",NULL);
    nivel1 = load_bitmap("img/nivel1.bmp",NULL);
    nivel2 = load_bitmap("img/nivel2.bmp",NULL);
    nivel3 = load_bitmap("img/nivel3.bmp",NULL);
    presione = load_bitmap("img/presione.bmp",NULL);
    teclas = load_bitmap("img/teclas.bmp",NULL);
    logo = load_bitmap("img/LOGO.bmp",NULL);
    menu = load_bitmap("img/opciones.bmp",NULL);
    jugarl = load_bitmap("img/jugar.bmp",NULL);
    reglas = load_bitmap("img/reglas.bmp",NULL);
    salir = load_bitmap("img/salir.bmp",NULL);
    copi = load_bitmap("img/copy.bmp",NULL);
    instr = load_bitmap("img/instr.bmp",NULL);
    a1 = load_bitmap("frames/1.bmp",NULL);
    a2 = load_bitmap("frames/2.bmp",NULL);
    a3 = load_bitmap("frames/3.bmp",NULL);
    a4 = load_bitmap("frames/4.bmp",NULL);
    a5 = load_bitmap("frames/5.bmp",NULL);
    a6 = load_bitmap("frames/6.bmp",NULL);
    a7 = load_bitmap("frames/7.bmp",NULL);

    b1 = load_bitmap("frames1/b1.bmp",NULL);
    b2 = load_bitmap("frames1/b2.bmp",NULL);
    b3 = load_bitmap("frames1/b3.bmp",NULL);
    b4 = load_bitmap("frames1/b4.bmp",NULL);
    b5 = load_bitmap("frames1/b5.bmp",NULL);
    b6 = load_bitmap("frames1/b6.bmp",NULL);
    b7 = load_bitmap("frames1/b7.bmp",NULL);


        do{

        px=12*30;
        py=10*30;
        mov[0] = 0;
        mov[1] = 0;
        mov[2] = 0;
        i = 0;

        /*****************************************************************************************************/

        men(op); // Inicializar Menu

        /*****************************************************************************************************/

        /** Dependiendo de la opcion que se elija en el menu, se cumplira una condicion **/

        if(op[0] == 1){

        nivel=1;
        play_midi(musica,1);
        if(nivel == 1){

            clear_keybuf(); // Limpiar el buffer del teclado.

                   do{ // Nombre Del Jugador - Detectar String.

                lt='z';

                if( lt>='a' && lt<= 'z'){


                textprintf(screen,font,120,120,makeacol(250,134,31,0),"INTRODUCE TU NOMBRE: ");
                textprintf(screen,font,120,250,makeacol(106,200,243,0),"PRESIONA ENTER CUANDO ESTES LISTO.");
                lt=readkey();
                textprintf(screen,font,300+10*i,120,makeacol(160,243,106,0),"%c",lt);
                if(key[KEY_BACKSPACE] && i >= 0){
                    i--;
                    lt = ' ';
                    cadena[i]=lt;
                    cadena[i+1] = '\0';
                    textprintf(screen,font,300+10*i,120,makeacol(160,243,106,0),"%c",lt);
                }
                else if(lt != 13){
                    cadena[i]=lt;
                    cadena[i+1]='\0' ;
                    i++;
                }
                }

            }while( lt!=13 && i < 40 );


            clear(screen);
        do{
            draw_sprite(screen,nivel1,100,200);
            rest(400);
            draw_sprite(screen,presione,100,350);
            rest(400);
            clear(screen);

        }while(!keypressed());
        clear(buffer);
        genera_mapa1();
        jugar(mov,cadena);
        if(nivel == 1){
           nivel=2;
           levelup++;
        }
        }


        clear(screen);
        clear(buffer);
        rest(100);


        /** NIVEL 2 **/

        if(nivel == 2){
            clear_keybuf();
        do{
            draw_sprite(screen,nivel2,100,200);
            rest(400);
            draw_sprite(screen,presione,100,350);
            rest(400);
            clear(screen);
        }while(!keypressed());
        clear(buffer);
        py=6*30;px=9*30;
        genera_mapa2();
        jugar(mov,cadena);
        if(nivel == 2){
            nivel = 3;
            levelup++;
        }
        }



        clear(screen);
        clear(buffer);
        rest(100);


        /** NIVEL 3**/

        if(nivel == 3){
            clear_keybuf();
        do{
            draw_sprite(screen,nivel3,100,200);
            rest(400);
            draw_sprite(screen,presione,100,350);
            rest(400);
            clear(screen);
        }while(!keypressed());
        py=3*30;px=7*30;
        genera_mapa3();
        jugar(mov,cadena);
        if(nivel == 3){
            levelup++;
            nivel = 4;
        }
       }
       }

        if(op[0] == 2){
            clear(screen);
            draw_sprite(screen,instr,60,20);
            readkey();
            op[0] = 1;
            nivel = 1;
        }
        if(op[0] == 3){
            nivel = 6;
            op[0] = 0;
        }

        /// CUANDO SE TERMINA EL JUEGO GANAR O PERDER RETORNA VALOR NIVEL = 4 -- MOSTRAR ESTADISTICAS ///

        if(nivel == 4 || nivel == 5){

            if(nivel == 4){
                play_midi(good,1);
                clear(buffer);
                clear(screen);
                textprintf(screen,font,250,200,makeacol(210,250,31,0)," FELICITACIONES HAS GANADO TODO EL JUEGO. ");
                rest(4000);
            }
            else{
                play_midi(msd,1);
                clear(buffer);
                clear(screen);
                textprintf(screen,font,250,200,makeacol(210,250,31,0)," HAS PERDIDO. JUEGO TERMINADO. ");
                rest(4000);
            }

            movmax = mov[0] + mov[1] + mov[2];
            clear(buffer);
            clear(screen);
            textprintf(screen,font,300,200,makeacol(210,250,31,0),"NIVELES LOGRADOS: %d.",levelup);
            rest(3000);
            clear(screen);
            textprintf(screen,font,150,200,makeacol(210,250,31,0),"MOVIMIENTOS TOTALES %d.",movmax);
            textprintf(screen,font,150,250,makeacol(210,250,31,0),"MOVIMIENTOS NIVEL 1: %d.",mov[0]);
            textprintf(screen,font,150,300,makeacol(210,250,31,0),"MOVIMIENTOS NIVEL 2: %d.",mov[1]);
            textprintf(screen,font,150,350,makeacol(210,250,31,0),"MOVIMIENTOS NIVEL 3: %d.",mov[2]);
            rest(5000);
            clear(screen);
            textprintf(screen,font,300,200,makeacol(210,250,31,0),"GRACIAS POR JUGAR");
            textprintf(screen,font,150,300,makeacol(100,200,31,0),"PROYECTO DESARROLLADO POR: LUIS FERNANDO VARGAS GOMEZ ");
            textprintf(screen,font,150,350,makeacol(100,200,31,0),"UNIVERSIDAD NACIONAL EXPERIMENTAL DEL TACHIRA. (UNET)");
            rest(5000);
            clear(screen);
            textprintf(screen,font,300,200,makeacol(192,65,240,0),"DESEA VOLVER AL MENU? (S/N): ");
            rest(2500);
            clear_keybuf();
            readkey();
            if(key[KEY_S] || key[KEY_ENTER] ){
                op[0] = 1;
                levelup = 0;
            }
            else{
                op[0]=0;
                break;
            }
        }

    }while(op[0] == 1);

    return 0;
}
END_OF_MAIN();

void men(int op[1]){ // MENU

    op[0] = 1;
    play_midi(mm,1);
    int r;


    /********************************************************************************************/
    /********************************************************************************************/

    do{
    if(op[0] == 1){

        clear(screen);
        clear_keybuf();
        do{

        if(keypressed()){
            break;
        }

        draw_sprite(screen,logo,170,5);
        draw_sprite(screen,jugarl,350,150);
        draw_sprite(screen,copi,270,450);
        draw_sprite(screen,a1,90,200);

        if(keypressed()){
            break;
        }

        rest(100);
        draw_sprite(screen,b1,520,180);

        if(keypressed()){
            break;
        }


        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a2,90,200);
        draw_sprite(screen,b2,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a3,90,200);
        draw_sprite(screen,b3,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a4,90,200);
        draw_sprite(screen,b4,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a5,90,200);
        draw_sprite(screen,b5,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a6,90,200);
        draw_sprite(screen,b6,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a7,90,200);
        draw_sprite(screen,b7,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        clear(screen);

        }while( !keypressed() );

        readkey();
        if(key[KEY_S]){
            op[0] = 2;
        }
        if(key[KEY_W]){
            op[0] = 3;
        }
        clear(screen);
    }
    /********************************************************************************************/
    /********************************************************************************************/


    if(op[0] == 2){

        clear(screen);
        clear_keybuf();
        do{

         if(keypressed()){
            break;
        }

        draw_sprite(screen,logo,170,5);
        draw_sprite(screen,reglas,350,150);
        draw_sprite(screen,copi,270,450);
        draw_sprite(screen,a1,90,200);

        if(keypressed()){
            break;
        }

        rest(100);
        draw_sprite(screen,b1,520,180);

        if(keypressed()){
            break;
        }


        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a2,90,200);
        draw_sprite(screen,b2,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a3,90,200);
        draw_sprite(screen,b3,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a4,90,200);
        draw_sprite(screen,b4,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a5,90,200);
        draw_sprite(screen,b5,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a6,90,200);
        draw_sprite(screen,b6,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a7,90,200);
        draw_sprite(screen,b7,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        clear(screen);

        }while( !keypressed() );


        readkey();
        if(key[KEY_S]){
            op[0] = 3;
        }
        if(key[KEY_W]){
            op[0] = 1;
        }
        clear(screen);
    }
/********************************************************************************************/
/********************************************************************************************/



        if(op[0] == 3){
        clear(screen);
        do{

        if(keypressed()){
            break;
        }

        draw_sprite(screen,logo,170,5);
        draw_sprite(screen,salir,350,150);
        draw_sprite(screen,copi,270,450);
        draw_sprite(screen,a1,90,200);

        if(keypressed()){
            break;
        }

        rest(100);

        draw_sprite(screen,b1,520,180);

        if(keypressed()){
            break;
        }


        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a2,90,200);
        draw_sprite(screen,b2,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a3,90,200);
        draw_sprite(screen,b3,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a4,90,200);
        draw_sprite(screen,b4,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a5,90,200);
        draw_sprite(screen,b5,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a6,90,200);
        draw_sprite(screen,b6,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        draw_sprite(screen,a7,90,200);
        draw_sprite(screen,b7,520,180);
        rest(200);

        if(keypressed()){
            break;
        }

        clear(screen);

        }while( !keypressed() );
        readkey();
        if(key[KEY_S]){
            op[0] = 1;
        }
        if(key[KEY_W]){
            op[0] = 2;
        }
        clear(screen);
    }

    if(key[KEY_ESC]){
        op[0] = 4;
    }
    if(key[KEY_ENTER]){
       play_midi(goal,0);
        rest(3000);
        break;
    }

    }while(!key[KEY_ESC]);

    /********************************************************************************************/
    /********************************************************************************************/

}

void genera_mapa1(){

    int i,j;

    int mapa1[13][20] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,3,0,0,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,0,0,3,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,0,0,3,0,3,0,1,0,0,0,0,0,0,0,0,0,
    0,1,1,1,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,
    0,1,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,8,8,1,  // [8][17] [8][18]
    0,1,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,8,8,1,  // [9][17]  [9][18]
    0,1,1,1,1,1,0,1,1,1,0,1,2,1,1,0,0,8,8,1,  // [10][17]  [10][18]
    0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
};

    for(i = 0 ; i < 13 ; i++){
        for(j = 0 ; j < 20 ; j++){
            mapa[i][j] = mapa1[i][j];
        }
    }

}

void genera_mapa2(){

    int i,j;

    int mapa2[13][20] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
    0,0,1,8,8,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,  // [3][3] [3][4]
    0,0,1,8,8,0,0,1,0,3,0,0,3,0,0,1,0,0,0,0,  // [4][3] [4][4]
    0,0,1,8,8,0,0,1,3,1,1,1,1,0,0,1,0,0,0,0,  // [5][3] [5][4]
    0,0,1,8,8,0,0,0,0,2,0,1,1,0,0,1,0,0,0,0,  // [6][3] [6][4]
    0,0,1,8,8,0,0,1,0,1,0,0,3,0,1,1,0,0,0,0,  // [7][3] [7][4]
    0,0,1,1,1,1,1,1,0,1,1,3,0,3,0,1,0,0,0,0,
    0,0,0,0,1,0,3,0,0,3,0,3,0,3,0,1,0,0,0,0,
    0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

    for(i = 0 ; i < 13 ; i++){
        for(j = 0 ; j < 20 ; j++){
            mapa[i][j] = mapa2[i][j];
        }
    }




}

void genera_mapa3(){

    int i,j;

    int mapa3[13][20] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,
    0,0,1,1,0,1,0,0,1,1,0,3,3,0,1,0,0,0,0,0,
    0,0,1,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,1,0,0,3,0,0,1,1,1,0,0,0,1,0,0,0,0,0,
    0,0,1,1,1,0,1,1,1,1,1,3,1,1,1,0,0,0,0,0,
    0,0,1,0,3,0,0,1,1,1,0,8,8,1,0,0,0,0,0,0, //          [7][11]  [7][12]
    0,0,1,0,3,0,3,0,3,0,8,8,8,1,0,0,0,0,0,0, // [8][10]  [8][11]  [8][12]
    0,0,1,0,0,0,0,1,1,1,8,8,8,1,0,0,0,0,0,0, // [9][10]  [9][11]  [9[12]
    0,0,1,0,3,3,0,1,0,1,8,8,8,1,0,0,0,0,0,0, // [10][10] [10][11] [10][12]
    0,0,1,0,0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,
    0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

    for(i = 0 ; i < 13 ; i++){
        for(j = 0 ; j < 20 ; j++){
            mapa[i][j] = mapa3[i][j];
        }
    }

}

void imprimir_controles(){ // IMPRIME LISTA DE CONTROLES
    draw_sprite(buffer,teclas,550,30);
    textprintf(buffer,font,549,5*30,-2,"TECLAS DE MOVIMIENTO");
}

void dibujar_mapa(char cadena[40]){ // IMPRIME EL MAPA
    int i,j;


    for(i = 0 ; i < 13 ; i++ ){
        for(j = 0 ; j < 20 ; j++){
            if(mapa[i][j] == 1){
                draw_sprite(buffer,muro,j*30,i*30);
            }
            if(mapa[i][j] == 3){
                draw_sprite(buffer,box,j*30,i*30);
            }
            if(mapa[i][j] == 8){
                draw_sprite(buffer,star,j*30,i*30);
            }
        }
    }

    textprintf(buffer,font,140,450,makeacol(84,240,65,0),"NOMBRE DEL JUGADOR: %s .",cadena);
    imprimir_controles();

}

void mostrar(){ // ORDENAR IMPRIMIR TODO EN LA PANTALLA
    blit(buffer, screen, 0,0,0,0,880,600);
}

void asignar_casillas(){ // ASIGNA LOS VALORES DE LLEGADA A LA MATRIZ
    int i,j;

    if(nivel == 1){
        for(i = 8 ; i < 11 ; i++){
            for(j = 17 ; j <= 18 ; j++){
                if(mapa[i][j] == 0){
                    mapa[i][j] = 8;
                }
            }
        }
    }
    if(nivel == 2){
        for(i = 3 ; i < 8 ; i++){
            for(j = 3 ; j <= 4 ; j++){
                if(mapa[i][j] == 0){
                    mapa[i][j] = 8;
                }
            }
        }
    }
    if(nivel == 3){
            if(mapa[7][11] == 0){
                mapa[7][11] = 8;
            }
            if(mapa[7][12] == 0){
                mapa[7][12] = 8;
            }
        for(i = 8 ; i < 11 ; i++){
            for(j = 10 ; j < 13 ; j++){
                if(mapa[i][j] == 0){
                    mapa[i][j] = 8;
                }
            }
        }
    }


}

void mover_cajas(){ // LOGICA DEL MOVIMIENTO DE CAJAS

    int i,j;
                //Mover Cajas.
            for(i = 0 ; i < 12 ; i++){
                for(j = 0 ; j < 20 ; j++){

                if(mapa[i][j] == 3){
                if(py/30 == i && px/30 == j && dir == 0 && (mapa[i][j-1] == 0 || mapa[i][j-1] == 8)){ // Izquierda
                    mapa[i][j]= 0;
                    mapa[i][j-1]= 3;
                }
                else if(py/30 == i && px/30 == j && dir == 1 && (mapa[i][j+1] == 0 || mapa[i][j+1] == 8)){ // Derecha
                    mapa[i][j]= 0;
                    mapa[i][j+1]= 3;
                }
                else if(py/30 == i && px/30 == j && dir == 2 && (mapa[i+1][j] == 0 || mapa[i+1][j] == 8) ) { // Abajo
                    mapa[i][j]= 0;
                    mapa[i+1][j]= 3;
                }
                else if(py/30 == i && px/30 == j && dir == 3 && (mapa[i-1][j] == 0 || mapa[i-1][j] == 8) ){ // Arriba
                    mapa[i][j]= 0;
                    mapa[i-1][j]= 3;
                }


                else if(py/30 == i && px/30 == j && dir == 0 && mapa[i][j-1] != 0){ // Detectar Obstaculo Izquierda
                    px+=30;
                    dir = 4;
                }
                else if(py/30 == i && px/30 == j && dir == 1 && mapa[i][j+1] != 0) { // Detectar Obstaculo Derecha
                    px-=30;
                    dir = 4;
                }
                else if(py/30 == i && px/30 == j && dir == 2 && mapa[i+1][j] != 0){ // Detectar Obstaculo Abajo
                    py-=30;
                    dir = 4;
                }
                else if(py/30 == i && px/30 == j && dir == 3 && mapa[i-1][j] != 0){ // Detectar Obstaculo Arriba
                    py+=30;
                    dir = 4;
                }
                }

                }
            }




}

void dibujar_pj(){ // DIBUJA PERSONAJE PRINCIPAL
    draw_sprite(buffer,pj,px,py);
}

bool detecta_perder(){ // DETECTA LAS CASILLAS DONDE NO HAY ES POSIBLE SACAR LAS CAJAS

    if(nivel == 1){
        if (mapa[3][6] == 3 || mapa[3][7] == 3 || mapa[3][8] == 3 || mapa[6][4] == 3 || mapa [6][9] == 3 || mapa[8][2] == 3 || mapa[8][15] == 3 || mapa[9][2] == 3 || mapa[10][15] == 3 || mapa [11][6] == 3 || mapa[11][10] == 3){
            return true;
        }
        else if( (mapa[7][6] == 3 && mapa[8][6] == 3) ||  (mapa[9][3] && mapa[9][4] == 3) || (mapa[9][11] == 3&& mapa[9][12] == 3)  || (mapa[9][12] == 3&& mapa[9][13] == 3) || (mapa[9][13] == 3 && mapa[9][14] == 3) || (mapa[6][7] == 3 && mapa[6][8] == 3) ){
            return true;
        }
    }


    if(nivel == 2){
        if(mapa[3][6] == 3 || mapa[3][9] == 3 || mapa[3][8] == 3 || mapa[3][10] == 3 || mapa[3][11] == 3 || mapa[3][12] == 3 || mapa[4][14] == 3 || mapa[5][14] == 3 || mapa[6][14] == 3 || mapa[6][10] == 3 || mapa[7][10] == 3 || mapa[8][14] == 3 || mapa[7][6] == 3 || mapa[9][5] == 3 || mapa[9][14] == 3 || mapa[10][5] == 3 || mapa[10][6] == 3 || mapa[10][7] == 3 || mapa[10][8] == 3 || mapa[10][10] == 3 || mapa[10][11] == 3 || mapa[10][12] == 3 || mapa[10][13] == 3 || mapa[10][14] == 3){
            return true;
        }
        else if( (mapa[7][8] == 3 && mapa[9][9] == 3) || (mapa[8][8] == 3 && mapa[9][9] == 3) || (mapa[4][9] == 3 && mapa[4][10] == 3) || (mapa[4][10] == 3 && mapa[4][11] == 3) || (mapa[4][11] == 3 && mapa[4][12] == 3) || (mapa[9][9] == 3 && mapa[9][10] == 3)){
            return true;
        }
    }

    if(nivel == 3){
         if( mapa[5][7] == 3 || mapa[2][10] == 3 || mapa[2][11] == 3 || mapa[2][12] == 3 || mapa[3][4] == 3 || mapa[3][13] == 3 || mapa[4][3] == 3 || mapa[3][6] == 3 || mapa[6][7] == 3 || mapa[4][13] == 3 || mapa[5][3] == 3 || mapa[3][7] == 3 || mapa[5][13] == 3 || mapa[7][3] == 3 || mapa[7][6] == 3 || mapa[7][10] == 3 || mapa[8][3] == 3 || mapa[9][3] == 3 || mapa[10][3] == 3 || mapa[10][6] == 3 || mapa[11][3] == 3 || mapa[11][4] == 3){
            return true;
         }
         else if( (mapa[9][6] == 3 && mapa[10][5] == 3) || (mapa[4][8] == 3 && mapa[4][9] == 3)  || (mapa[4][9] == 3 && mapa[4][10] == 3) || (mapa[8][8] == 3 && mapa[8][9] == 3) || (mapa[8][7] == 3 && mapa[8][8] == 3) ){
            return true;
         }
    }

    return false;
}

bool comprobar_ganar(){ // COMPRUEBA QUE TODAS LAS CAJAS ESTEN EN SU LUGAR

    if(nivel == 1){
    if(mapa[8][17] == 3 && mapa[8][18] == 3 && mapa[9][17] == 3 && mapa[9][18] == 3 && mapa[10][17] == 3 && mapa[10][18] == 3){
        return false;
    }
    }

    if(nivel == 2){
    if(mapa[3][3] == 3 && mapa[3][4] == 3 && mapa[4][3] == 3 && mapa[4][4] == 3 && mapa[5][3] == 3 && mapa[5][4] == 3 && mapa[6][3] == 3 && mapa[6][4] == 3 && mapa[7][3] == 3 && mapa[7][4] == 3 ){
        return false;
    }
    }
    if(nivel == 3){
    if(mapa[7][11] == 3 && mapa[7][12] == 3 && mapa[8][10] == 3 && mapa[8][11] == 3 && mapa[8][12] == 3 && mapa[9][10] == 3 && mapa[9][11] == 3 && mapa[9][12] == 3 && mapa[10][10] == 3 && mapa[10][11] == 3  && mapa[10][12] == 3){
        return false;
    }
    }



    return true;
}

void jugar(int mov[3],char cadena[40]){ // LOGICA DEL JUEGO, MOVIMIENTO, DETECCION , DIBUJO .



        do{
            dibujar_mapa(cadena);
            clear(buffer);


            if(detecta_perder()){
                clear(buffer);
                textprintf(buffer,font,150,480,-2,"SE HA DETECTADO, OBSTACULO DESEA SALIR? PULSE [X].");
                readkey;
                if(key[KEY_X]){
                    nivel = 5;
                    clear_keybuf();
                   play_midi(death,0);
                    rest(4000);
                    break;
                }
            }

            if(key[KEY_X]){
                nivel = 5;
                clear_keybuf();
                play_midi(death,0);
                rest(4000);
                break;
            }

            if(nivel == 1){
            textprintf(buffer,font,5*30,14*30,-2,"NUMERO DE MOVIMIENTOS : %d.",mov[0]);
            }
            if(nivel == 2){
            textprintf(buffer,font,5*30,14*30,-2,"NUMERO DE MOVIMIENTOS : %d.",mov[1]);
            }
            if(nivel == 3){
            textprintf(buffer,font,5*30,14*30,-2,"NUMERO DE MOVIMIENTOS : %d.",mov[2]);
            }


            dibujar_mapa(cadena);
            dibujar_pj();
            mostrar();
            rest(80);

            while(!keypressed()) {}
            readkey();

            rest(7);



            if(key[KEY_A]){
                dir = 0;
            }
            else if (key[KEY_D]){
                dir = 1;
            }
            else if (key[KEY_S]){
                dir = 2;
            }
            else if (key[KEY_W]){
                dir = 3;
            }
            else{
                dir = 4;
            }


            if(dir == 0){
                if(mapa[py/30][(px-30)/30] != 1){
                    px-=30;
                }
                else{
                    dir = 4;
                }
            }





            if(dir == 1){
                    if(mapa[py/30][(px+30)/30] != 1){
                        px+=30;
                    }
                    else{
                        dir = 4;
                    }
                }

            if(dir == 2){

                if(mapa[ (py+30) /30 ][ (px/30)] != 1){
                    py+=30;
                }
                else{
                    dir = 4;
                }
            }

            if(dir == 3){
                if(mapa[(py-30)/30][px/30] != 1){
                    py-=30;
                }
                else{
                    dir = 4;
                }
            }

            dibujar_mapa(cadena);
            mover_cajas();



            if(nivel == 1 && dir != 4){
                mov[0]++;
            }
            if(nivel == 2 && dir != 4){
                mov[1]++;
            }
            if(nivel == 3 && dir != 4){
                mov[2]++;
            }
            asignar_casillas();


        }while(comprobar_ganar());

}
