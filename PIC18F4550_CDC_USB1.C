

#include <18F4550.h> // DefiniTION DE REGISTRE INTERNE.

#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN

// Fuses :
/*
HSPLL: utilizamos un cristal HS de alta velocidad, en conjunto con el PLL para generar los 48Mhz.
NOMCLR: Utilizamos reset por software, y dejamos el pin 1 del micro como entrada/salida digital.
NOWDT: No utilizamos el perro guard�an.
NOPROTECT: Desactivamos la protecci�n de c�digo.
NOLVP: Desactivamos la programaci�n a bajo voltaje.
NODEBUG: No entramos al modo debug.
USBDIV: signfica que el clock del usb se tomar� del PLL/2 = 96Mhz/2 = 48Mhz.
PLL5: significa que el PLL prescaler dividir� en 5 la frecuencia del cristal. para HS = 20Mhz/5 = 4Mhz.
CPUDIV1: El PLL postscaler decide la divisi�n en 2 de la frecuencia de salida del PLL de 96MHZ, si queremos 48MHZ, lo dejamos como est�.
VREGEN: habilita el regulador de 3.3 volts que usa el m�dulo USB
*/

#use delay(clock=48000000) // fr�quence maximale(full speed USB).

#include "usb_cdc.h" // Description des functions du USB.
#include "usb_desc_cdc.h" // Descripteur USB.


// Fonctions du statut du port USB.
void usb_connecte(void) {
output_high(PIN_A0);
output_low(PIN_A1);
}
void usb_deconnecte(void) {
output_high(PIN_A1);
output_low(PIN_A0);
}
void usb_enumere(void) {
output_high(PIN_A2);
}

void commande_moteur(void) {
output_low(PIN_B1);
output_low(PIN_B2);
output_low(PIN_B3);

int i,j,k;

           if(usb_cdc_getc()=='l'){ // si le pic re�oit le caract�re l                
              output_toggle(PIN_B1); // Commutation d'�tat du relais du moteur 1 .
                   i = i+1;
                   if ((i%2) == 0)   {
                    printf(usb_cdc_putc, "moteur M1 en arret.\n\r");
                       }               
                              else {
                                 printf(usb_cdc_putc, "moteur M1 en marche.\n\r");
                                    }                           
                                     }
                   
                   if(usb_cdc_getc()=='m'){ // si le pic re�oit le caract�re m                  
              output_toggle(PIN_B2); // Commutation d'�tat du relais du moteur 2 .
                   j = j+1;
                   if ((j%2) == 0)   {
                    printf(usb_cdc_putc, "moteur M2 en arret.\n\r");
                       }             
                              else {
                                 printf(usb_cdc_putc, "moteur M2 en marche.\n\r");
                                    }
                                      }
                   if(usb_cdc_getc()=='n'){ // si le pic re�oit le caract�re n                
              output_toggle(PIN_B3); // Commutation d'�tat du relais du moteur 3 .
                   k = k+1;
                   if ((k%2) == 0)   {
                    printf(usb_cdc_putc, "moteur M3 en arret.\n\r");
                       }                 
                              else {
                                 printf(usb_cdc_putc, "moteur M3 en marche.\n\r");
                                    }                             
                                          }

}


void main() {
set_tris_a(0x00); // Configuration des ports A & B en sortie
set_tris_b(0x00);

   usb_cdc_init(); // initialisation du COM Virtuel.
   usb_init(); // Initialisation du stack USB.
   while(!usb_cdc_connected()) {
   usb_deconnecte();
   }
   usb_connecte();    // Verification de la connection PC__PIC
   do{
      usb_task();
      if (usb_enumerated()){  // Si le pic est enumere par le PC.
      usb_enumere(); // LED enumeration_ON (red).
         if(usb_cdc_kbhit()){ // Reception de nouveaux donn�es.
               commande_moteur();      }         
      }
      }while (TRUE); // boucle infinie.
   
}
