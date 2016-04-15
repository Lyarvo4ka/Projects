namespace OfficeTestFiles
{
    partial class OfficeTester
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OfficeTester));
            this.button1 = new System.Windows.Forms.Button();
            this.EditDirPath = new System.Windows.Forms.TextBox();
            this.OpenDirDialog = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.checkWord = new System.Windows.Forms.CheckBox();
            this.checkExel = new System.Windows.Forms.CheckBox();
            this.checkPowerPoint = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.TextReport = new System.Windows.Forms.RichTextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.EditCountExel = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.EditCountWord = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            resources.ApplyResources(this.button1, "button1");
            this.button1.ForeColor = System.Drawing.Color.ForestGreen;
            this.button1.Name = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // EditDirPath
            // 
            resources.ApplyResources(this.EditDirPath, "EditDirPath");
            this.EditDirPath.Name = "EditDirPath";
            // 
            // OpenDirDialog
            // 
            resources.ApplyResources(this.OpenDirDialog, "OpenDirDialog");
            this.OpenDirDialog.Name = "OpenDirDialog";
            this.OpenDirDialog.UseVisualStyleBackColor = true;
            this.OpenDirDialog.Click += new System.EventHandler(this.OpenDirDialog_Click);
            // 
            // groupBox1
            // 
            resources.ApplyResources(this.groupBox1, "groupBox1");
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.TabStop = false;
            // 
            // progressBar1
            // 
            resources.ApplyResources(this.progressBar1, "progressBar1");
            this.progressBar1.Name = "progressBar1";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button1);
            resources.ApplyResources(this.groupBox2, "groupBox2");
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.TabStop = false;
            // 
            // checkWord
            // 
            resources.ApplyResources(this.checkWord, "checkWord");
            this.checkWord.Checked = true;
            this.checkWord.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkWord.Name = "checkWord";
            this.checkWord.UseVisualStyleBackColor = true;
            // 
            // checkExel
            // 
            resources.ApplyResources(this.checkExel, "checkExel");
            this.checkExel.Checked = true;
            this.checkExel.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkExel.Name = "checkExel";
            this.checkExel.UseVisualStyleBackColor = true;
            // 
            // checkPowerPoint
            // 
            resources.ApplyResources(this.checkPowerPoint, "checkPowerPoint");
            this.checkPowerPoint.Checked = true;
            this.checkPowerPoint.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkPowerPoint.Name = "checkPowerPoint";
            this.checkPowerPoint.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            resources.ApplyResources(this.groupBox3, "groupBox3");
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.TabStop = false;
            // 
            // TextReport
            // 
            resources.ApplyResources(this.TextReport, "TextReport");
            this.TextReport.Name = "TextReport";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.TextReport);
            resources.ApplyResources(this.groupBox4, "groupBox4");
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.TabStop = false;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.EditCountExel);
            this.groupBox5.Controls.Add(this.label2);
            this.groupBox5.Controls.Add(this.EditCountWord);
            this.groupBox5.Controls.Add(this.label1);
            resources.ApplyResources(this.groupBox5, "groupBox5");
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.TabStop = false;
            // 
            // EditCountExel
            // 
            resources.ApplyResources(this.EditCountExel, "EditCountExel");
            this.EditCountExel.Name = "EditCountExel";
            this.EditCountExel.ReadOnly = true;
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // EditCountWord
            // 
            resources.ApplyResources(this.EditCountWord, "EditCountWord");
            this.EditCountWord.Name = "EditCountWord";
            this.EditCountWord.ReadOnly = true;
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // OfficeTester
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.checkPowerPoint);
            this.Controls.Add(this.checkExel);
            this.Controls.Add(this.checkWord);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.OpenDirDialog);
            this.Controls.Add(this.EditDirPath);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Name = "OfficeTester";
            this.groupBox2.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox EditDirPath;
        private System.Windows.Forms.Button OpenDirDialog;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkWord;
        private System.Windows.Forms.CheckBox checkExel;
        private System.Windows.Forms.CheckBox checkPowerPoint;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RichTextBox TextReport;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox EditCountWord;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox EditCountExel;
        private System.Windows.Forms.Label label2;
    }
}

