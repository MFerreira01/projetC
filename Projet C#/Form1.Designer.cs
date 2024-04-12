namespace Projet_Cpp
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            bt_select = new Button();
            cb_treatment = new ComboBox();
            pb_init = new PictureBox();
            pb_GT = new PictureBox();
            pb_result = new PictureBox();
            label1 = new Label();
            label2 = new Label();
            bt_treatment = new Button();
            bt_save_image = new Button();
            bt_saveIOU = new Button();
            bt_calculate_IOU = new Button();
            label3 = new Label();
            txtBox_IOU = new TextBox();
            openFileDialog = new OpenFileDialog();
            pb1 = new PictureBox();
            pb2 = new PictureBox();
            pb3 = new PictureBox();
            pb4 = new PictureBox();
            pb5 = new PictureBox();
            pb6 = new PictureBox();
            pb7 = new PictureBox();
            pb8 = new PictureBox();
            ScrollBar1 = new HScrollBar();
            checkBox1 = new CheckBox();
            bt_m90 = new Button();
            bt_p90 = new Button();
            ((System.ComponentModel.ISupportInitialize)pb_init).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb_GT).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb_result).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb2).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb3).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb4).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb5).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb6).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb7).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pb8).BeginInit();
            SuspendLayout();
            // 
            // bt_select
            // 
            bt_select.Location = new Point(33, 29);
            bt_select.Name = "bt_select";
            bt_select.Size = new Size(160, 34);
            bt_select.TabIndex = 0;
            bt_select.Text = "Sélection images";
            bt_select.UseVisualStyleBackColor = true;
            bt_select.Click += bt_select_Click;
            // 
            // cb_treatment
            // 
            cb_treatment.DropDownStyle = ComboBoxStyle.DropDownList;
            cb_treatment.FormattingEnabled = true;
            cb_treatment.Items.AddRange(new object[] { "Initale", "Rotation" });
            cb_treatment.Location = new Point(212, 30);
            cb_treatment.Name = "cb_treatment";
            cb_treatment.Size = new Size(134, 33);
            cb_treatment.TabIndex = 1;
            cb_treatment.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            // 
            // pb_init
            // 
            pb_init.BackColor = SystemColors.ControlLightLight;
            pb_init.BorderStyle = BorderStyle.FixedSingle;
            pb_init.Location = new Point(40, 245);
            pb_init.Name = "pb_init";
            pb_init.Size = new Size(460, 460);
            pb_init.SizeMode = PictureBoxSizeMode.StretchImage;
            pb_init.TabIndex = 3;
            pb_init.TabStop = false;
            // 
            // pb_GT
            // 
            pb_GT.BackColor = SystemColors.ControlLightLight;
            pb_GT.BorderStyle = BorderStyle.FixedSingle;
            pb_GT.Location = new Point(575, 248);
            pb_GT.Name = "pb_GT";
            pb_GT.Size = new Size(200, 200);
            pb_GT.TabIndex = 4;
            pb_GT.TabStop = false;
            // 
            // pb_result
            // 
            pb_result.BackColor = SystemColors.ControlLightLight;
            pb_result.BorderStyle = BorderStyle.FixedSingle;
            pb_result.Location = new Point(575, 484);
            pb_result.Name = "pb_result";
            pb_result.Size = new Size(200, 200);
            pb_result.TabIndex = 5;
            pb_result.TabStop = false;
            pb_result.Click += pb_result_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(618, 448);
            label1.Name = "label1";
            label1.Size = new Size(115, 25);
            label1.TabIndex = 6;
            label1.Text = "Ground truth";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.BackColor = Color.Transparent;
            label2.Location = new Point(638, 684);
            label2.Name = "label2";
            label2.Size = new Size(74, 25);
            label2.TabIndex = 7;
            label2.Text = "Résultat";
            label2.Click += label2_Click;
            // 
            // bt_treatment
            // 
            bt_treatment.Location = new Point(104, 761);
            bt_treatment.Name = "bt_treatment";
            bt_treatment.Size = new Size(134, 56);
            bt_treatment.TabIndex = 8;
            bt_treatment.Text = "Traiter";
            bt_treatment.UseVisualStyleBackColor = true;
            // 
            // bt_save_image
            // 
            bt_save_image.Location = new Point(572, 761);
            bt_save_image.Name = "bt_save_image";
            bt_save_image.Size = new Size(196, 56);
            bt_save_image.TabIndex = 11;
            bt_save_image.Text = "Enregistrer Résultat";
            bt_save_image.UseVisualStyleBackColor = true;
            bt_save_image.Click += bt_save_image_Click;
            // 
            // bt_saveIOU
            // 
            bt_saveIOU.Location = new Point(572, 859);
            bt_saveIOU.Name = "bt_saveIOU";
            bt_saveIOU.Size = new Size(196, 56);
            bt_saveIOU.TabIndex = 12;
            bt_saveIOU.Text = "Exporter résultat IOU";
            bt_saveIOU.UseVisualStyleBackColor = true;
            bt_saveIOU.Click += bt_saveIOU_Click;
            // 
            // bt_calculate_IOU
            // 
            bt_calculate_IOU.Location = new Point(334, 761);
            bt_calculate_IOU.Name = "bt_calculate_IOU";
            bt_calculate_IOU.Size = new Size(129, 56);
            bt_calculate_IOU.TabIndex = 14;
            bt_calculate_IOU.Text = "Calculer IOU";
            bt_calculate_IOU.Click += bt_calculate_IOU_Click;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(62, 875);
            label3.Name = "label3";
            label3.Size = new Size(201, 25);
            label3.TabIndex = 15;
            label3.Text = "Score IOU :                 %";
            // 
            // txtBox_IOU
            // 
            txtBox_IOU.Enabled = false;
            txtBox_IOU.Location = new Point(159, 872);
            txtBox_IOU.Name = "txtBox_IOU";
            txtBox_IOU.Size = new Size(79, 31);
            txtBox_IOU.TabIndex = 16;
            // 
            // openFileDialog
            // 
            openFileDialog.FileName = "openFileDialog";
            openFileDialog.Multiselect = true;
            // 
            // pb1
            // 
            pb1.BackColor = SystemColors.ControlLightLight;
            pb1.Location = new Point(12, 93);
            pb1.Name = "pb1";
            pb1.Size = new Size(100, 100);
            pb1.SizeMode = PictureBoxSizeMode.StretchImage;
            pb1.TabIndex = 17;
            pb1.TabStop = false;
            pb1.Click += pb1_Click;
            // 
            // pb2
            // 
            pb2.BackColor = SystemColors.ControlLightLight;
            pb2.Location = new Point(112, 93);
            pb2.Name = "pb2";
            pb2.Size = new Size(100, 100);
            pb2.SizeMode = PictureBoxSizeMode.StretchImage;
            pb2.TabIndex = 18;
            pb2.TabStop = false;
            pb2.Click += pb2_Click;
            // 
            // pb3
            // 
            pb3.BackColor = SystemColors.ControlLightLight;
            pb3.Location = new Point(212, 93);
            pb3.Name = "pb3";
            pb3.Size = new Size(100, 100);
            pb3.SizeMode = PictureBoxSizeMode.StretchImage;
            pb3.TabIndex = 19;
            pb3.TabStop = false;
            pb3.Click += pb3_Click;
            // 
            // pb4
            // 
            pb4.BackColor = SystemColors.ControlLightLight;
            pb4.Location = new Point(312, 93);
            pb4.Name = "pb4";
            pb4.Size = new Size(100, 100);
            pb4.SizeMode = PictureBoxSizeMode.StretchImage;
            pb4.TabIndex = 20;
            pb4.TabStop = false;
            pb4.Click += pb4_Click;
            // 
            // pb5
            // 
            pb5.BackColor = SystemColors.ControlLightLight;
            pb5.Location = new Point(412, 93);
            pb5.Name = "pb5";
            pb5.Size = new Size(100, 100);
            pb5.SizeMode = PictureBoxSizeMode.StretchImage;
            pb5.TabIndex = 21;
            pb5.TabStop = false;
            pb5.Click += pb5_Click;
            // 
            // pb6
            // 
            pb6.BackColor = SystemColors.ControlLightLight;
            pb6.Location = new Point(512, 93);
            pb6.Name = "pb6";
            pb6.Size = new Size(100, 100);
            pb6.SizeMode = PictureBoxSizeMode.StretchImage;
            pb6.TabIndex = 22;
            pb6.TabStop = false;
            pb6.Click += pb6_Click;
            // 
            // pb7
            // 
            pb7.BackColor = SystemColors.ControlLightLight;
            pb7.Location = new Point(612, 93);
            pb7.Name = "pb7";
            pb7.Size = new Size(100, 100);
            pb7.SizeMode = PictureBoxSizeMode.StretchImage;
            pb7.TabIndex = 23;
            pb7.TabStop = false;
            pb7.Click += pb7_Click;
            // 
            // pb8
            // 
            pb8.BackColor = SystemColors.ControlLightLight;
            pb8.Location = new Point(712, 93);
            pb8.Name = "pb8";
            pb8.Size = new Size(100, 100);
            pb8.SizeMode = PictureBoxSizeMode.StretchImage;
            pb8.TabIndex = 24;
            pb8.TabStop = false;
            pb8.Click += pb8_Click;
            // 
            // ScrollBar1
            // 
            ScrollBar1.Location = new Point(12, 193);
            ScrollBar1.Name = "ScrollBar1";
            ScrollBar1.Size = new Size(800, 25);
            ScrollBar1.TabIndex = 26;
            ScrollBar1.Scroll += ScrollBar1_Scroll;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(586, 32);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(226, 29);
            checkBox1.TabIndex = 27;
            checkBox1.Text = "Traitement automatique";
            checkBox1.UseVisualStyleBackColor = true;
            checkBox1.CheckedChanged += checkBox1_CheckedChanged;
            // 
            // bt_m90
            // 
            bt_m90.Location = new Point(372, 30);
            bt_m90.Name = "bt_m90";
            bt_m90.Size = new Size(61, 33);
            bt_m90.TabIndex = 28;
            bt_m90.Text = "-90°";
            bt_m90.UseVisualStyleBackColor = true;
            bt_m90.Click += bt_m90_Click;
            // 
            // bt_p90
            // 
            bt_p90.Location = new Point(439, 30);
            bt_p90.Name = "bt_p90";
            bt_p90.Size = new Size(61, 33);
            bt_p90.TabIndex = 29;
            bt_p90.Text = "+90°";
            bt_p90.UseVisualStyleBackColor = true;
            bt_p90.Click += bt_p90_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(823, 939);
            Controls.Add(bt_p90);
            Controls.Add(bt_m90);
            Controls.Add(checkBox1);
            Controls.Add(ScrollBar1);
            Controls.Add(pb8);
            Controls.Add(pb7);
            Controls.Add(pb6);
            Controls.Add(pb5);
            Controls.Add(pb4);
            Controls.Add(pb3);
            Controls.Add(pb2);
            Controls.Add(pb1);
            Controls.Add(txtBox_IOU);
            Controls.Add(label3);
            Controls.Add(bt_calculate_IOU);
            Controls.Add(bt_saveIOU);
            Controls.Add(bt_save_image);
            Controls.Add(bt_treatment);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(pb_result);
            Controls.Add(pb_GT);
            Controls.Add(pb_init);
            Controls.Add(cb_treatment);
            Controls.Add(bt_select);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)pb_init).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb_GT).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb_result).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb1).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb2).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb3).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb4).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb5).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb6).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb7).EndInit();
            ((System.ComponentModel.ISupportInitialize)pb8).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button bt_select;
        private ComboBox cb_treatment;
        private PictureBox pb_init;
        private PictureBox pb_GT;
        private PictureBox pb_result;
        private Label label1;
        private Label label2;
        private Button bt_treatment;
        private Button bt_save_image;
        private Button bt_saveIOU;
        private Button bt_calculate_IOU;
        private Label label3;
        private TextBox txtBox_IOU;
        private OpenFileDialog openFileDialog;
        private PictureBox pb1;
        private PictureBox pb2;
        private PictureBox pb3;
        private PictureBox pb4;
        private PictureBox pb5;
        private PictureBox pb6;
        private PictureBox pb7;
        private PictureBox pb8;
        private HScrollBar ScrollBar1;
        private CheckBox checkBox1;
        private Button bt_m90;
        private Button bt_p90;
    }
}