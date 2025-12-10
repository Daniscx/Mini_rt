# Archivos de Escena miniRT

Este directorio contiene archivos de prueba para el proyecto miniRT.

## Archivos Disponibles

### test.rt
Escena de prueba básica con múltiples esferas de colores:
- 3 esferas (roja, verde, azul)
- 1 plano como suelo
- 1 luz puntual
- Luz ambiental

### simple.rt
Escena minimalista para pruebas básicas:
- 1 esfera azul grande
- 1 luz puntual cenital
- Luz ambiental moderada

### cylinder.rt
Prueba de cilindro con objetos adicionales:
- 1 cilindro vertical verde
- 1 esfera roja
- 1 plano como suelo
- 1 luz puntual

### multiple_lights.rt
Escena con múltiples fuentes de luz:
- 3 esferas
- 2 luces puntuales (roja y azul)
- Luz ambiental tenue
- Plano como suelo

## Formato de los Archivos

Cada línea representa un elemento:
- **A**: Luz ambiental (ratio, RGB)
- **C**: Cámara (posición, dirección, FOV)
- **L**: Luz puntual (posición, intensidad, RGB)
- **sp**: Esfera (centro, diámetro, RGB)
- **pl**: Plano (punto, normal, RGB)
- **cy**: Cilindro (centro, eje, diámetro, altura, RGB)

## Uso

```bash
./miniRT scenes/test.rt
./miniRT scenes/simple.rt
./miniRT scenes/cylinder.rt
./miniRT scenes/multiple_lights.rt
```
