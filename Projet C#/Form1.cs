using System.Drawing.Imaging;
using System.Reflection.PortableExecutable;
using System.Windows.Forms;
using static System.Windows.Forms.AxHost;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System;
using System.IO;
using System.Text;


namespace Projet_Cpp
{
    public partial class Form1 : Form
    {
        string[] selectedFiles = null;
        string[] filesGT = null;
        int valueScroll = 0;
        int valueScrollH_init;
        int valueScrollV_init;

        Bitmap imageTraitement;
        Bitmap imageGR;

        // Pour zoom
        double zoom = 1.0;

        // ScrollBar

        // IOU
        List<double> IOU_CSV = new List<double>();

        public Form1()
        {
            InitializeComponent();
            bt_m90.Visible = false;
            bt_p90.Visible = false;
            trackBar_time.Visible = false;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cb_treatment.SelectedItem.ToString() == "Initiale")
            {
                bt_m90.Visible = false;
                bt_p90.Visible = false;

            }

            if (cb_treatment.SelectedItem.ToString() == "Rotation")
            {
                bt_m90.Visible = true;
                bt_p90.Visible = true;

            }
        }

        private void bt_select_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Image Files (*.png; *.jpg; *.jpeg; *.gif; *.bmp)|*.png; *.jpg; *.jpeg; *.gif; *.bmp|All files (*.*)|*.*";
            openFileDialog.ShowDialog();
            selectedFiles = openFileDialog.FileNames;

            string old1 = "Source Images - bmp";
            string news1 = "Ground truth - png";
            filesGT = new string[selectedFiles.Length];
            Array.Copy(selectedFiles, filesGT, selectedFiles.Length);
            for (int i = 0; i < filesGT.Length; i++)
            {
                filesGT[i] = filesGT[i].Replace(old1, news1);
            }

            string old2 = "bmp";
            string news2 = "png";
            for (int i = 0; i < filesGT.Length; i++)
            {
                filesGT[i] = filesGT[i].Replace(old2, news2);
            }

            ScrollBar1.Maximum = selectedFiles.Length - 8;
            if (selectedFiles.Length >= 1)
                pb1.Image = Image.FromFile(selectedFiles[0]);
            if (selectedFiles.Length >= 2)
                pb2.Image = Image.FromFile(selectedFiles[1]);
            if (selectedFiles.Length >= 3)
                pb3.Image = Image.FromFile(selectedFiles[2]);
            if (selectedFiles.Length >= 4)
                pb4.Image = Image.FromFile(selectedFiles[3]);
            if (selectedFiles.Length >= 5)
                pb5.Image = Image.FromFile(selectedFiles[4]);
            if (selectedFiles.Length >= 6)
                pb6.Image = Image.FromFile(selectedFiles[5]);
            if (selectedFiles.Length >= 7)
                pb7.Image = Image.FromFile(selectedFiles[6]);
            if (selectedFiles.Length >= 8)
                pb8.Image = Image.FromFile(selectedFiles[7]);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void pb_all_Click(object sender, EventArgs e)
        {
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void bt_calculate_IOU_Click(object sender, EventArgs e)
        {
            double resultIOU = 0.0;

            if (checkBox1.Checked)
            {


                // Ecrire le score IOU en passant chaque image
                txtBox_IOU.Text = resultIOU.ToString();
                // Mettre le résultat dans la liste
                IOU_CSV.Add(resultIOU);
            }
            else
            {


                txtBox_IOU.Text = resultIOU.ToString();
                // Mettre le résultat dans la liste
                IOU_CSV.Add(resultIOU);
            }
        }

        private void ScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            valueScroll = ScrollBar1.Value;
            pb1.Image = Image.FromFile(selectedFiles[valueScroll + 1]);
            pb2.Image = Image.FromFile(selectedFiles[valueScroll + 2]);
            pb3.Image = Image.FromFile(selectedFiles[valueScroll + 3]);
            pb4.Image = Image.FromFile(selectedFiles[valueScroll + 4]);
            pb5.Image = Image.FromFile(selectedFiles[valueScroll + 5]);
            pb6.Image = Image.FromFile(selectedFiles[valueScroll + 6]);
            pb7.Image = Image.FromFile(selectedFiles[valueScroll + 7]);
            pb8.Image = Image.FromFile(selectedFiles[valueScroll + 8]);

        }

        private void bt_zmoins_Click(object sender, EventArgs e)
        {
            //if (zoom > 1)
            //{
            //    zoom = zoom / 2;
            //    int newHeight = 2 * pb_init.Image.Height;
            //    int newWidth = 2 * pb_init.Image.Width;
            //    if (newHeight <= imageTraitement.Height || newWidth <= imageTraitement.Width)
            //    {
            //        Bitmap imagetemp = new Bitmap(newWidth, newHeight);
            //        for (int y = 0; y < newHeight; y++)
            //        {
            //            for (int x = 0; x < newWidth; x++)
            //            {
            //                Color pixelColor = imageTraitement.GetPixel(x, y);
            //                imagetemp.SetPixel(x, y, Color.FromArgb(pixelColor.R, pixelColor.R, pixelColor.R));
            //            }
            //        }

            //        pb_init.Image = imagetemp;

            //        vScrollBar1.Maximum = imageTraitement.Height / (int)zoom;
            //        hScrollBar1.Maximum = imageTraitement.Width / (int)zoom;
            //    }
            //}
        }


        private void bt_zplus_Click(object sender, EventArgs e)
        {
            //if (zoom <= 16)
            //{
            //    zoom = zoom * 2;
            //    int newHeight = imageTraitement.Height / (int)zoom;
            //    int newWidth = imageTraitement.Width / (int)zoom;

            //    Bitmap imagetemp = new Bitmap(newWidth, newHeight);
            //    for (int y = 0; y < newHeight; y++)
            //    {
            //        for (int x = 0; x < newWidth; x++)
            //        {
            //            Color pixelColor = imageTraitement.GetPixel(x, y);
            //            imagetemp.SetPixel(x, y,Color.FromArgb(pixelColor.R,pixelColor.R,pixelColor.R));
            //        }
            //    }

            //    pb_init.Image = imagetemp;

            //    vScrollBar1.Maximum = imageTraitement.Height;
            //    hScrollBar1.Maximum = imageTraitement.Width;
            //}
        }

        private void bt_m90_Click(object sender, EventArgs e)
        {
            Image image_temp = pb_init.Image;
            Image GT_temp = pb_GT.Image;
            image_temp.RotateFlip(RotateFlipType.Rotate270FlipNone);
            GT_temp.RotateFlip(RotateFlipType.Rotate270FlipNone);
            pb_init.Image = image_temp;
            pb_GT.Image = GT_temp;
        }

        private void bt_p90_Click(object sender, EventArgs e)
        {
            Image image_temp = pb_init.Image;
            Image GT_temp = pb_GT.Image;
            image_temp.RotateFlip(RotateFlipType.Rotate90FlipNone);
            GT_temp.RotateFlip(RotateFlipType.Rotate90FlipNone);
            pb_init.Image = image_temp;
            pb_GT.Image = GT_temp;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                trackBar_time.Visible = true;
            }
            if (!checkBox1.Checked)
            {
                trackBar_time.Visible = false;
            }

        }

        private void pb1_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb1.Image;
            if (pb1.Image != null)
            {
                imageTraitement = new Bitmap(pb1.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll]);
            }
        }

        private void pb2_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb2.Image;
            if (pb2.Image != null)
            {
                imageTraitement = new Bitmap(pb2.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 1]);
            }
        }

        private void pb3_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb3.Image;
            if (pb3.Image != null)
            {
                imageTraitement = new Bitmap(pb3.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 2]);
            }
        }

        private void pb4_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb4.Image;
            if (pb4.Image != null)
            {
                imageTraitement = new Bitmap(pb4.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 3]);
            }
        }

        private void pb5_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb5.Image;
            if (pb5.Image != null)
            {
                imageTraitement = new Bitmap(pb5.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 4]);
            }
        }

        private void pb6_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb6.Image;
            if (pb6.Image != null)
            {
                imageTraitement = new Bitmap(pb6.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 5]);
            }
        }

        private void pb7_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb7.Image;
            if (pb7.Image != null)
            {
                imageTraitement = new Bitmap(pb7.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 6]);
            }
        }

        private void pb8_Click(object sender, EventArgs e)
        {
            zoom = 1;
            pb_init.Image = pb8.Image;
            if (pb8.Image != null)
            {
                imageTraitement = new Bitmap(pb8.Image);
                pb_GT.Image = Image.FromFile(filesGT[valueScroll + 7]);
            }
        }

        private void pb_result_Click(object sender, EventArgs e)
        {

        }

        private void bt_saveIOU_Click(object sender, EventArgs e)
        {
            using (StreamWriter writer = new StreamWriter("D:\\Perso\\TELECOM\\GIT\\projetC\\resultat\\data_IOU.csv"))
            {
                foreach (var line in IOU_CSV)
                {
                    writer.WriteLine(string.Join(",", line));
                }
            }
        }
        int nbImageSave = 1;
        private void bt_save_image_Click(object sender, EventArgs e)
        {
            if (pb_result.Image != null)
            {
                string filename = "Image" + nbImageSave;
                pb_result.Image.Save(filename, ImageFormat.Bmp);

                nbImageSave += 1;
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {

        }
    }
}