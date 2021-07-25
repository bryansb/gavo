#include <opencv2/core/core.hpp> // Contiene los elementos base de OpenCV (matrices, arreglos, etc.)
#include <opencv2/highgui/highgui.hpp> // Contiene estructuras para crear la interfaz gráfica
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer determinados formatos de imágenes
#include <opencv2/video/video.hpp> // Procesamiento y escritura
#include <opencv2/videoio/videoio.hpp> // de video

#include <opencv2/objdetect/objdetect.hpp> // Librería para detección de objetos (contiene el HOG Descriptor)

using namespace cv; // El espacio de nombres donde están definidas algunas funciones de OpenCV