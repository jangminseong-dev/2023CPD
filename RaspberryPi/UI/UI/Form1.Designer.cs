namespace UI
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            label_co2 = new Label();
            label_temp = new Label();
            label1 = new Label();
            label2 = new Label();
            SuspendLayout();
            // 
            // label_co2
            // 
            label_co2.AutoSize = true;
            label_co2.BackColor = Color.Transparent;
            label_co2.Font = new Font("Noto Sans KR Medium", 35F, FontStyle.Bold, GraphicsUnit.Point);
            label_co2.ForeColor = Color.White;
            label_co2.Location = new Point(315, 547);
            label_co2.Margin = new Padding(2, 0, 2, 0);
            label_co2.MinimumSize = new Size(150, 64);
            label_co2.Name = "label_co2";
            label_co2.Size = new Size(150, 68);
            label_co2.TabIndex = 0;
            label_co2.Text = "432";
            label_co2.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label_temp
            // 
            label_temp.AutoSize = true;
            label_temp.BackColor = Color.Transparent;
            label_temp.Font = new Font("Noto Sans KR", 12F, FontStyle.Regular, GraphicsUnit.Point);
            label_temp.ForeColor = Color.White;
            label_temp.Location = new Point(188, 221);
            label_temp.Margin = new Padding(2, 0, 2, 0);
            label_temp.MinimumSize = new Size(34, 22);
            label_temp.Name = "label_temp";
            label_temp.Size = new Size(34, 23);
            label_temp.TabIndex = 1;
            label_temp.Text = "24";
            label_temp.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Noto Sans KR", 12F, FontStyle.Regular, GraphicsUnit.Point);
            label1.ForeColor = Color.White;
            label1.Location = new Point(389, 221);
            label1.Margin = new Padding(2, 0, 2, 0);
            label1.MinimumSize = new Size(28, 22);
            label1.Name = "label1";
            label1.Size = new Size(28, 23);
            label1.TabIndex = 2;
            label1.Text = "68";
            label1.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.BackColor = Color.Transparent;
            label2.Font = new Font("Noto Sans KR", 12F, FontStyle.Regular, GraphicsUnit.Point);
            label2.ForeColor = Color.White;
            label2.Location = new Point(592, 221);
            label2.Margin = new Padding(2, 0, 2, 0);
            label2.MinimumSize = new Size(37, 22);
            label2.Name = "label2";
            label2.Size = new Size(37, 23);
            label2.TabIndex = 3;
            label2.Text = "1";
            label2.TextAlign = ContentAlignment.MiddleRight;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSize = true;
            BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
            ClientSize = new Size(800, 1107);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(label_temp);
            Controls.Add(label_co2);
            FormBorderStyle = FormBorderStyle.None;
            Margin = new Padding(2, 1, 2, 1);
            MaximumSize = new Size(800, 1280);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label_co2;
        private Label label_temp;
        private Label label1;
        private Label label2;
    }
}