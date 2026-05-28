Обработка изображений на C

Проект по компьютерному зрению. Реализованы основные алгоритмы обработки изображений.

Сборка проекта:
make

Как запустить:
./imgproc input.png -median 3 output.png

Фильтры:
- Медианный (-median 3) - убирает шум
- Гауссов (-gauss 3) - размывает картинку
- Детекция границ (-edges 100) - находит контуры

Примеры:
./imgproc photo.png -median 3 clean.png
./imgproc photo.png -gauss 3 blur.png
./imgproc photo.png -edges 100 edges.png

Структура:
main.c - главная программа
filters.c - все фильтры
image.c - загрузка и сохранение картинок
Makefile - сборка

Ссылка: https://github.com/dvdkrn/computer-vision
