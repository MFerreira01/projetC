using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Projet_Cpp
{
    public partial class Form1 : Form
    {
        string pathImage = null;
        string[] selectedFiles = null;
        int valueScroll = 0;
        double zoom = 1.0;

        public Form1()
        {
            InitializeComponent();
            bt_m90.Visible = false;
            bt_p90.Visible = false;
            bt_zmoins.Visible = false;
            bt_zplus.Visible = false;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cb_treatment.SelectedItem.ToString() == "Initiale")
            {
                bt_m90.Visible = false;
                bt_p90.Visible = false;
                bt_zmoins.Visible = false;
                bt_zplus.Visible = false;
            }
            if (cb_treatment.SelectedItem.ToString() == "Rotation")
            {
                bt_m90.Visible = false;
                bt_p90.Visible = false;
                bt_zmoins.Visible = true;
                bt_zplus.Visible = true;

            }

            if (cb_treatment.SelectedItem.ToString() == "Zoom")
            {
                bt_p90.Visible = true;
                bt_m90.Visible = true;
                bt_zmoins.Visible = false;
                bt_zplus.Visible = false;

            }
        }

        private void bt_select_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Image Files (*.png; *.jpg; *.jpeg; *.gif; *.bmp)|*.png; *.jpg; *.jpeg; *.gif; *.bmp|All files (*.*)|*.*";
            openFileDialog.ShowDialog();
            selectedFiles = openFileDialog.FileNames;
            ScrollBar1.Maximum = selectedFiles.Length;
            pb1.Image = Image.FromFile(selectedFiles[1]);
            pb2.Image = Image.FromFile(selectedFiles[2]);
            pb3.Image = Image.FromFile(selectedFiles[3]);
            pb4.Image = Image.FromFile(selectedFiles[4]);
            pb5.Image = Image.FromFile(selectedFiles[5]);
            pb6.Image = Image.FromFile(selectedFiles[6]);
            pb7.Image = Image.FromFile(selectedFiles[7]);
            pb8.Image = Image.FromFile(selectedFiles[8]);
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

        private void button6_Click(object sender, EventArgs e)
        {

        }

        private void ScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            valueScroll = ScrollBar1.Value;
            pb1.Image = Image.FromFile(selectedFiles[valueScroll]);
            pb2.Image = Image.FromFile(selectedFiles[valueScroll + 1]);
            pb3.Image = Image.FromFile(selectedFiles[valueScroll + 2]);
            pb4.Image = Image.FromFile(selectedFiles[valueScroll + 3]);
            pb5.Image = Image.FromFile(selectedFiles[valueScroll + 4]);
            pb6.Image = Image.FromFile(selectedFiles[valueScroll + 5]);
            pb7.Image = Image.FromFile(selectedFiles[valueScroll + 6]);
            pb8.Image = Image.FromFile(selectedFiles[valueScroll + 7]);

        }

        private void bt_zmoins_Click(object sender, EventArgs e)
        {
            if (zoom >= 0.5)
                zoom = zoom / 2;
        }

        private void bt_zplus_Click(object sender, EventArgs e)
        {
            if (zoom <= 16)
                zoom = zoom * 2;
        }

        private void bt_m90_Click(object sender, EventArgs e)
        {
            Image image_temp = pb_init.Image;
            image_temp.RotateFlip(RotateFlipType.Rotate270FlipNone);
            pb_init.Image = image_temp;
        }

        private void bt_p90_Click(object sender, EventArgs e)
        {
            Image image_temp = pb_init.Image;
            image_temp.RotateFlip(RotateFlipType.Rotate90FlipNone);
            pb_init.Image = image_temp;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (!checkBox1.Checked)
            {

            }
        }
    }
}