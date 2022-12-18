using System;
using OpenCvSharp;
using Microsoft.Win32;
using System.Windows.Media.Imaging;

namespace lab_3
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : System.Windows.Window
    {
        string fileName;
        bool load = false;
        public MainWindow()
        {
            InitializeComponent();
        }
        private void showWindow(Mat dst, string name)
        {
            Cv2.Resize(dst, dst, new OpenCvSharp.Size(imageBox.Width, imageBox.Height));
            Cv2.ImShow(name, dst);
        }
        private void load_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            if (openFileDialog.ShowDialog() == true)
            {
                fileName = openFileDialog.FileName;
                imageBox.Source = new BitmapImage(new Uri(fileName));

                textLoad.Foreground = System.Windows.Media.Brushes.Black;
                load = true;
            }
        }

        private void gaussian_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (load == true)
            {
                Mat src = new Mat(fileName);
                Mat dst = new Mat();

                int size = (int)gauss_ksize.Value;
                Cv2.GaussianBlur(src, dst, new OpenCvSharp.Size(size, size), 
                    gauss_sigmax.Value, gauss_sigmay.Value, BorderTypes.Default);

                showWindow(dst, "gaussian");
            }
            else
                textLoad.Foreground = System.Windows.Media.Brushes.OrangeRed;

        }

        private void median_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (load == true)
            {
                Mat src = new Mat(fileName);
                Mat dst = new Mat();

                Cv2.MedianBlur(src, dst, (int)median_ksize.Value);

                showWindow(dst, "median");
            }
            else
                textLoad.Foreground = System.Windows.Media.Brushes.OrangeRed;
        }

        private void blur_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (load == true)
            {
                Mat src = new Mat(fileName);
                Mat dst = new Mat();

                int size = (int)blue_ksize.Value;
                Cv2.Blur(src, dst, new OpenCvSharp.Size(size, size));

                showWindow(dst, "blur");
            }
            else
                textLoad.Foreground = System.Windows.Media.Brushes.OrangeRed;
        }

        private void adaptive_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (load == true)
            {
                Mat src = new Mat(fileName, 0);
                Mat dst = new Mat();

                Cv2.AdaptiveThreshold(src, dst, adaptive_max.Value, AdaptiveThresholdTypes.MeanC, 
                    ThresholdTypes.Binary, (int)adaptive_blocksize.Value, 3);

                showWindow(dst, "adaptive");
            }
            else
                textLoad.Foreground = System.Windows.Media.Brushes.OrangeRed;
        }

        private void bernsen_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (load == true)
            {
                Mat src = new Mat(fileName, 0);
                Mat dst = Mat.Zeros(src.Size(), src.Type());

                int r = 15;
                double eps = 15.0;
                int border = (r - 1) / 2;
                Mat result = new Mat(src.Rows, src.Cols, src.Type());
                Cv2.CopyMakeBorder(src, result, border, border, border, border, BorderTypes.Replicate);

                for (int i = border; i < result.Rows - border; i++)
                {
                    for (int j = border; j < result.Cols - border; j++)
                    {
                        Mat square = result.SubMat(new Rect(j - border, i - border, r, r));

                        double min, max;
                        Cv2.MinMaxLoc(square, out min, out max);
                        double c = max - min, t;

                        if (c > eps)
                            t = (min + max) / 2.0;
                        else
                            t = 0;

                        byte value = result.Get<byte>(i, j);

                        if (value > t)
                            value = 255;
                        else
                            value = 0;

                        dst.Set(i - border, j - border, value);
                    }

                }
                showWindow(dst, "bernsen");
            }
            else
                textLoad.Foreground = System.Windows.Media.Brushes.OrangeRed;
        }

        private void niblack_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (load == true)
            {
                Mat src = new Mat(fileName, 0);
                Mat dst = Mat.Zeros(src.Size(), src.Type());

                int r = 15;
                double k = -0.2;
                int border = (r - 1) / 2;
                Mat result = new Mat(src.Rows, src.Cols, src.Type());
                Cv2.CopyMakeBorder(src, result, border, border, border, border, BorderTypes.Replicate);

                for (int i = border; i < result.Rows - border; i++)
                {
                    for (int j = border; j < result.Cols - border; j++)
                    {
                        Mat square = result.SubMat(new Rect(j - border, i - border, r, r));

                        Scalar mean = new Scalar();
                        Scalar dev = new Scalar();
                        Cv2.MeanStdDev(square, out mean, out dev);

                        double t = mean.Val0 + k * dev.Val0;

                        byte value = result.Get<byte>(i, j);

                        if (value > t)
                            value = 255;
                        else
                            value = 0;

                        dst.Set(i - border, j - border, value);
                    }
                }
                showWindow(dst, "niblack");
            }
            else
                textLoad.Foreground = System.Windows.Media.Brushes.OrangeRed;
        }
    }
}
