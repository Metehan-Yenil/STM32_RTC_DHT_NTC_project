namespace RobotFinal
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
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            lblTarihSaat = new Label();
            btnTarihSaatAyarla = new Button();
            button2 = new Button();
            lblReceivedData = new Label();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(89, 34);
            label1.Name = "label1";
            label1.Size = new Size(125, 20);
            label1.TabIndex = 0;
            label1.Text = "NTC temperature:";
            label1.Click += label1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(89, 84);
            label2.Name = "label2";
            label2.Size = new Size(144, 20);
            label2.TabIndex = 1;
            label2.Text = "DHT22 temperature:";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(89, 133);
            label3.Name = "label3";
            label3.Size = new Size(124, 20);
            label3.TabIndex = 2;
            label3.Text = "DHT22 humudity:";
            // 
            // lblTarihSaat
            // 
            lblTarihSaat.AutoSize = true;
            lblTarihSaat.Location = new Point(91, 187);
            lblTarihSaat.Name = "lblTarihSaat";
            lblTarihSaat.Size = new Size(113, 20);
            lblTarihSaat.TabIndex = 3;
            lblTarihSaat.Text = "Clock and Date:";
            // 
            // btnTarihSaatAyarla
            // 
            btnTarihSaatAyarla.Location = new Point(89, 308);
            btnTarihSaatAyarla.Name = "btnTarihSaatAyarla";
            btnTarihSaatAyarla.Size = new Size(255, 29);
            btnTarihSaatAyarla.TabIndex = 5;
            btnTarihSaatAyarla.Text = "Set Date and Clock";
            btnTarihSaatAyarla.UseVisualStyleBackColor = true;
            btnTarihSaatAyarla.Click += btnTarihSaatAyarla_Click;
            // 
            // button2
            // 
            button2.Location = new Point(499, 308);
            button2.Name = "button2";
            button2.Size = new Size(198, 29);
            button2.TabIndex = 6;
            button2.Text = "update Date and Clock";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // lblReceivedData
            // 
            lblReceivedData.AutoSize = true;
            lblReceivedData.Location = new Point(210, 35);
            lblReceivedData.Name = "lblReceivedData";
            lblReceivedData.Size = new Size(60, 20);
            lblReceivedData.TabIndex = 7;
            lblReceivedData.Text = "no data";
            lblReceivedData.Click += label4_Click;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(239, 84);
            label4.Name = "label4";
            label4.Size = new Size(60, 20);
            label4.TabIndex = 8;
            label4.Text = "no data";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(210, 133);
            label5.Name = "label5";
            label5.Size = new Size(60, 20);
            label5.TabIndex = 9;
            label5.Text = "no data";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(325, 187);
            label6.Name = "label6";
            label6.Size = new Size(0, 20);
            label6.TabIndex = 10;
            label6.Click += label6_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(label6);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(lblReceivedData);
            Controls.Add(button2);
            Controls.Add(btnTarihSaatAyarla);
            Controls.Add(lblTarihSaat);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "Form1";
            Text = "STM Uİ";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label lblTarihSaat;
        private Button btnTarihSaatAyarla;
        private Button button2;
        private Label lblReceivedData;
        private Label label4;
        private Label label5;
        private Label label6;
    }
}
