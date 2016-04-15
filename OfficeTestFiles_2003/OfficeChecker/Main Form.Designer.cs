namespace OfficeChecker
{
    partial class uiOfficeChecker
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.uiOpen = new System.Windows.Forms.Button();
            this.uiFolderPath = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.uiRTFcheck = new System.Windows.Forms.CheckBox();
            this.Group2003 = new System.Windows.Forms.GroupBox();
            this.uiCheckAll2003 = new System.Windows.Forms.CheckBox();
            this.uiWord2003check = new System.Windows.Forms.CheckBox();
            this.uiExcel2003Check = new System.Windows.Forms.CheckBox();
            this.uiPowerPoint2003Check = new System.Windows.Forms.CheckBox();
            this.GroupExel = new System.Windows.Forms.GroupBox();
            this.uiCheckAll2007 = new System.Windows.Forms.CheckBox();
            this.uiPowerPoint2007Check = new System.Windows.Forms.CheckBox();
            this.uiExcel2007Check = new System.Windows.Forms.CheckBox();
            this.uiWord2007check = new System.Windows.Forms.CheckBox();
            this.uiSTART = new System.Windows.Forms.Button();
            this.uiProgressBar = new System.Windows.Forms.ProgressBar();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.uiTextTimeOut = new System.Windows.Forms.TextBox();
            this.uiEnableTimeOut = new System.Windows.Forms.CheckBox();
            this.uiSTOP = new System.Windows.Forms.Button();
            this.uiRemainExcel = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.uiRemainWord = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.uiRemainPowerPoint = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.passwdCheck = new System.Windows.Forms.CheckBox();
            this.fileNameWord = new System.Windows.Forms.Label();
            this.fileNameExcel = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.Group2003.SuspendLayout();
            this.GroupExel.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.uiOpen);
            this.groupBox1.Controls.Add(this.uiFolderPath);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(376, 51);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Select Folder";
            // 
            // uiOpen
            // 
            this.uiOpen.Location = new System.Drawing.Point(295, 16);
            this.uiOpen.Name = "uiOpen";
            this.uiOpen.Size = new System.Drawing.Size(75, 23);
            this.uiOpen.TabIndex = 3;
            this.uiOpen.Text = "Open";
            this.uiOpen.UseVisualStyleBackColor = true;
            this.uiOpen.Click += new System.EventHandler(this.uiOpen_Click);
            // 
            // uiFolderPath
            // 
            this.uiFolderPath.Location = new System.Drawing.Point(6, 19);
            this.uiFolderPath.Name = "uiFolderPath";
            this.uiFolderPath.Size = new System.Drawing.Size(283, 20);
            this.uiFolderPath.TabIndex = 2;
            this.uiFolderPath.TextChanged += new System.EventHandler(this.uiFolderPath_TextChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.uiRTFcheck);
            this.groupBox2.Controls.Add(this.Group2003);
            this.groupBox2.Controls.Add(this.GroupExel);
            this.groupBox2.Location = new System.Drawing.Point(12, 64);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(194, 180);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Select File Types";
            // 
            // uiRTFcheck
            // 
            this.uiRTFcheck.AutoSize = true;
            this.uiRTFcheck.Checked = true;
            this.uiRTFcheck.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiRTFcheck.Location = new System.Drawing.Point(19, 129);
            this.uiRTFcheck.Name = "uiRTFcheck";
            this.uiRTFcheck.Size = new System.Drawing.Size(48, 17);
            this.uiRTFcheck.TabIndex = 4;
            this.uiRTFcheck.Text = "(*.rtf)";
            this.uiRTFcheck.UseVisualStyleBackColor = true;
            this.uiRTFcheck.CheckedChanged += new System.EventHandler(this.uiRTFcheck_CheckedChanged);
            // 
            // Group2003
            // 
            this.Group2003.Controls.Add(this.uiCheckAll2003);
            this.Group2003.Controls.Add(this.uiWord2003check);
            this.Group2003.Controls.Add(this.uiExcel2003Check);
            this.Group2003.Controls.Add(this.uiPowerPoint2003Check);
            this.Group2003.Location = new System.Drawing.Point(9, 18);
            this.Group2003.Name = "Group2003";
            this.Group2003.Size = new System.Drawing.Size(86, 105);
            this.Group2003.TabIndex = 6;
            this.Group2003.TabStop = false;
            this.Group2003.Text = "Office 2003";
            // 
            // uiCheckAll2003
            // 
            this.uiCheckAll2003.AutoSize = true;
            this.uiCheckAll2003.Checked = true;
            this.uiCheckAll2003.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiCheckAll2003.Location = new System.Drawing.Point(11, 86);
            this.uiCheckAll2003.Name = "uiCheckAll2003";
            this.uiCheckAll2003.Size = new System.Drawing.Size(70, 17);
            this.uiCheckAll2003.TabIndex = 3;
            this.uiCheckAll2003.Text = "Select All";
            this.uiCheckAll2003.UseVisualStyleBackColor = true;
            this.uiCheckAll2003.CheckedChanged += new System.EventHandler(this.uiCheckAll2003_CheckedChanged);
            // 
            // uiWord2003check
            // 
            this.uiWord2003check.AutoSize = true;
            this.uiWord2003check.Checked = true;
            this.uiWord2003check.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiWord2003check.Location = new System.Drawing.Point(11, 19);
            this.uiWord2003check.Name = "uiWord2003check";
            this.uiWord2003check.Size = new System.Drawing.Size(57, 17);
            this.uiWord2003check.TabIndex = 0;
            this.uiWord2003check.Text = "(*.doc)";
            this.uiWord2003check.UseVisualStyleBackColor = true;
            this.uiWord2003check.CheckedChanged += new System.EventHandler(this.uiWord2003check_CheckedChanged);
            // 
            // uiExcel2003Check
            // 
            this.uiExcel2003Check.AutoSize = true;
            this.uiExcel2003Check.Checked = true;
            this.uiExcel2003Check.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiExcel2003Check.Location = new System.Drawing.Point(11, 42);
            this.uiExcel2003Check.Name = "uiExcel2003Check";
            this.uiExcel2003Check.Size = new System.Drawing.Size(51, 17);
            this.uiExcel2003Check.TabIndex = 1;
            this.uiExcel2003Check.Text = "(*.xls)";
            this.uiExcel2003Check.UseVisualStyleBackColor = true;
            this.uiExcel2003Check.CheckedChanged += new System.EventHandler(this.uiExel2003Check_CheckedChanged);
            // 
            // uiPowerPoint2003Check
            // 
            this.uiPowerPoint2003Check.AutoSize = true;
            this.uiPowerPoint2003Check.Checked = true;
            this.uiPowerPoint2003Check.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiPowerPoint2003Check.Location = new System.Drawing.Point(11, 63);
            this.uiPowerPoint2003Check.Name = "uiPowerPoint2003Check";
            this.uiPowerPoint2003Check.Size = new System.Drawing.Size(54, 17);
            this.uiPowerPoint2003Check.TabIndex = 2;
            this.uiPowerPoint2003Check.Text = "(*.ppt)";
            this.uiPowerPoint2003Check.UseVisualStyleBackColor = true;
            this.uiPowerPoint2003Check.Visible = false;
            this.uiPowerPoint2003Check.CheckedChanged += new System.EventHandler(this.uiPowerPoint2003Check_CheckedChanged);
            // 
            // GroupExel
            // 
            this.GroupExel.Controls.Add(this.uiCheckAll2007);
            this.GroupExel.Controls.Add(this.uiPowerPoint2007Check);
            this.GroupExel.Controls.Add(this.uiExcel2007Check);
            this.GroupExel.Controls.Add(this.uiWord2007check);
            this.GroupExel.Location = new System.Drawing.Point(101, 18);
            this.GroupExel.Name = "GroupExel";
            this.GroupExel.Size = new System.Drawing.Size(86, 105);
            this.GroupExel.TabIndex = 6;
            this.GroupExel.TabStop = false;
            this.GroupExel.Text = "Office 2007";
            // 
            // uiCheckAll2007
            // 
            this.uiCheckAll2007.AutoSize = true;
            this.uiCheckAll2007.Checked = true;
            this.uiCheckAll2007.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiCheckAll2007.Location = new System.Drawing.Point(11, 86);
            this.uiCheckAll2007.Name = "uiCheckAll2007";
            this.uiCheckAll2007.Size = new System.Drawing.Size(70, 17);
            this.uiCheckAll2007.TabIndex = 6;
            this.uiCheckAll2007.Text = "Select All";
            this.uiCheckAll2007.UseVisualStyleBackColor = true;
            this.uiCheckAll2007.CheckedChanged += new System.EventHandler(this.uiCheckAll2007_CheckedChanged);
            // 
            // uiPowerPoint2007Check
            // 
            this.uiPowerPoint2007Check.AutoSize = true;
            this.uiPowerPoint2007Check.Checked = true;
            this.uiPowerPoint2007Check.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiPowerPoint2007Check.Location = new System.Drawing.Point(11, 65);
            this.uiPowerPoint2007Check.Name = "uiPowerPoint2007Check";
            this.uiPowerPoint2007Check.Size = new System.Drawing.Size(59, 17);
            this.uiPowerPoint2007Check.TabIndex = 5;
            this.uiPowerPoint2007Check.Text = "(*.pptx)";
            this.uiPowerPoint2007Check.UseVisualStyleBackColor = true;
            this.uiPowerPoint2007Check.Visible = false;
            this.uiPowerPoint2007Check.CheckedChanged += new System.EventHandler(this.uiPowerPoint2007Check_CheckedChanged);
            // 
            // uiExcel2007Check
            // 
            this.uiExcel2007Check.AutoSize = true;
            this.uiExcel2007Check.Checked = true;
            this.uiExcel2007Check.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiExcel2007Check.Location = new System.Drawing.Point(11, 42);
            this.uiExcel2007Check.Name = "uiExcel2007Check";
            this.uiExcel2007Check.Size = new System.Drawing.Size(56, 17);
            this.uiExcel2007Check.TabIndex = 4;
            this.uiExcel2007Check.Text = "(*.xlsx)";
            this.uiExcel2007Check.UseVisualStyleBackColor = true;
            this.uiExcel2007Check.CheckedChanged += new System.EventHandler(this.uiExel2007Check_CheckedChanged);
            // 
            // uiWord2007check
            // 
            this.uiWord2007check.AutoSize = true;
            this.uiWord2007check.Checked = true;
            this.uiWord2007check.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiWord2007check.Location = new System.Drawing.Point(11, 19);
            this.uiWord2007check.Name = "uiWord2007check";
            this.uiWord2007check.Size = new System.Drawing.Size(62, 17);
            this.uiWord2007check.TabIndex = 3;
            this.uiWord2007check.Text = "(*.docx)";
            this.uiWord2007check.UseVisualStyleBackColor = true;
            this.uiWord2007check.CheckedChanged += new System.EventHandler(this.uiWord2007check_CheckedChanged);
            // 
            // uiSTART
            // 
            this.uiSTART.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.uiSTART.Location = new System.Drawing.Point(120, 261);
            this.uiSTART.Name = "uiSTART";
            this.uiSTART.Size = new System.Drawing.Size(76, 32);
            this.uiSTART.TabIndex = 4;
            this.uiSTART.Text = "START";
            this.uiSTART.UseVisualStyleBackColor = true;
            this.uiSTART.Click += new System.EventHandler(this.uiSTART_Click);
            // 
            // uiProgressBar
            // 
            this.uiProgressBar.Location = new System.Drawing.Point(12, 304);
            this.uiProgressBar.Name = "uiProgressBar";
            this.uiProgressBar.Size = new System.Drawing.Size(376, 23);
            this.uiProgressBar.TabIndex = 6;
            this.uiProgressBar.Value = 79;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.uiTextTimeOut);
            this.groupBox4.Controls.Add(this.uiEnableTimeOut);
            this.groupBox4.Location = new System.Drawing.Point(212, 64);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(171, 62);
            this.groupBox4.TabIndex = 7;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Time Out (seconds)";
            // 
            // uiTextTimeOut
            // 
            this.uiTextTimeOut.Location = new System.Drawing.Point(7, 34);
            this.uiTextTimeOut.Name = "uiTextTimeOut";
            this.uiTextTimeOut.Size = new System.Drawing.Size(100, 20);
            this.uiTextTimeOut.TabIndex = 0;
            this.uiTextTimeOut.Text = "10";
            this.uiTextTimeOut.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.uiTextTimeOut_KeyPress);
            // 
            // uiEnableTimeOut
            // 
            this.uiEnableTimeOut.AutoSize = true;
            this.uiEnableTimeOut.Checked = true;
            this.uiEnableTimeOut.CheckState = System.Windows.Forms.CheckState.Checked;
            this.uiEnableTimeOut.Location = new System.Drawing.Point(7, 16);
            this.uiEnableTimeOut.Name = "uiEnableTimeOut";
            this.uiEnableTimeOut.Size = new System.Drawing.Size(86, 17);
            this.uiEnableTimeOut.TabIndex = 1;
            this.uiEnableTimeOut.Text = "Use Timeout";
            this.uiEnableTimeOut.UseVisualStyleBackColor = true;
            this.uiEnableTimeOut.CheckedChanged += new System.EventHandler(this.uiEnableTimeOut_CheckedChanged);
            // 
            // uiSTOP
            // 
            this.uiSTOP.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.uiSTOP.Location = new System.Drawing.Point(202, 261);
            this.uiSTOP.Name = "uiSTOP";
            this.uiSTOP.Size = new System.Drawing.Size(76, 32);
            this.uiSTOP.TabIndex = 9;
            this.uiSTOP.Text = "STOP";
            this.uiSTOP.UseVisualStyleBackColor = true;
            this.uiSTOP.Click += new System.EventHandler(this.uiSTOP_Click);
            // 
            // uiRemainExcel
            // 
            this.uiRemainExcel.Location = new System.Drawing.Point(94, 43);
            this.uiRemainExcel.Name = "uiRemainExcel";
            this.uiRemainExcel.ReadOnly = true;
            this.uiRemainExcel.Size = new System.Drawing.Size(60, 20);
            this.uiRemainExcel.TabIndex = 11;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(9, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "Word =";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(9, 46);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 13);
            this.label2.TabIndex = 14;
            this.label2.Text = "Excel =";
            // 
            // uiRemainWord
            // 
            this.uiRemainWord.Location = new System.Drawing.Point(94, 14);
            this.uiRemainWord.Name = "uiRemainWord";
            this.uiRemainWord.ReadOnly = true;
            this.uiRemainWord.Size = new System.Drawing.Size(60, 20);
            this.uiRemainWord.TabIndex = 13;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.uiRemainPowerPoint);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.uiRemainExcel);
            this.groupBox3.Controls.Add(this.uiRemainWord);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Location = new System.Drawing.Point(113, 333);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(160, 105);
            this.groupBox3.TabIndex = 15;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Remainig Files";
            // 
            // uiRemainPowerPoint
            // 
            this.uiRemainPowerPoint.Location = new System.Drawing.Point(94, 72);
            this.uiRemainPowerPoint.Name = "uiRemainPowerPoint";
            this.uiRemainPowerPoint.ReadOnly = true;
            this.uiRemainPowerPoint.Size = new System.Drawing.Size(60, 20);
            this.uiRemainPowerPoint.TabIndex = 15;
            this.uiRemainPowerPoint.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(6, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "PowerPoint =";
            this.label3.Visible = false;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.radioButton3);
            this.groupBox5.Controls.Add(this.radioButton2);
            this.groupBox5.Controls.Add(this.radioButton1);
            this.groupBox5.Location = new System.Drawing.Point(212, 132);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(171, 97);
            this.groupBox5.TabIndex = 16;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Not working files";
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(7, 66);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(145, 17);
            this.radioButton3.TabIndex = 2;
            this.radioButton3.Text = "Move to Folder (BadFiles)";
            this.radioButton3.UseVisualStyleBackColor = true;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.radioButton3_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(7, 43);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(79, 17);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.Text = "Remove All";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(7, 19);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(130, 17);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Rename to \".bad_file\"";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // passwdCheck
            // 
            this.passwdCheck.AutoSize = true;
            this.passwdCheck.Location = new System.Drawing.Point(219, 230);
            this.passwdCheck.Name = "passwdCheck";
            this.passwdCheck.Size = new System.Drawing.Size(151, 17);
            this.passwdCheck.TabIndex = 3;
            this.passwdCheck.Text = "password file to \".passwd\"";
            this.passwdCheck.UseVisualStyleBackColor = true;
            this.passwdCheck.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // fileNameWord
            // 
            this.fileNameWord.AutoSize = true;
            this.fileNameWord.Location = new System.Drawing.Point(15, 469);
            this.fileNameWord.Name = "fileNameWord";
            this.fileNameWord.Size = new System.Drawing.Size(85, 13);
            this.fileNameWord.TabIndex = 17;
            this.fileNameWord.Text = "Word current file";
            this.fileNameWord.Click += new System.EventHandler(this.label4_Click);
            // 
            // fileNameExcel
            // 
            this.fileNameExcel.AutoSize = true;
            this.fileNameExcel.Location = new System.Drawing.Point(13, 486);
            this.fileNameExcel.Name = "fileNameExcel";
            this.fileNameExcel.Size = new System.Drawing.Size(85, 13);
            this.fileNameExcel.TabIndex = 18;
            this.fileNameExcel.Text = "Excel current file";
            // 
            // uiOfficeChecker
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(523, 509);
            this.Controls.Add(this.fileNameExcel);
            this.Controls.Add(this.fileNameWord);
            this.Controls.Add(this.passwdCheck);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.uiSTOP);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.uiProgressBar);
            this.Controls.Add(this.uiSTART);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "uiOfficeChecker";
            this.Text = "Office Checker";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.Group2003.ResumeLayout(false);
            this.Group2003.PerformLayout();
            this.GroupExel.ResumeLayout(false);
            this.GroupExel.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button uiOpen;
        private System.Windows.Forms.TextBox uiFolderPath;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox uiExcel2003Check;
        private System.Windows.Forms.CheckBox uiWord2003check;
        private System.Windows.Forms.CheckBox uiPowerPoint2003Check;
        private System.Windows.Forms.Button uiSTART;
        private System.Windows.Forms.CheckBox uiPowerPoint2007Check;
        private System.Windows.Forms.CheckBox uiExcel2007Check;
        private System.Windows.Forms.CheckBox uiWord2007check;
        private System.Windows.Forms.GroupBox Group2003;
        private System.Windows.Forms.GroupBox GroupExel;
        private System.Windows.Forms.CheckBox uiCheckAll2003;
        private System.Windows.Forms.CheckBox uiCheckAll2007;
        private System.Windows.Forms.CheckBox uiRTFcheck;
        private System.Windows.Forms.ProgressBar uiProgressBar;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox uiTextTimeOut;
        private System.Windows.Forms.Button uiSTOP;
        private System.Windows.Forms.TextBox uiRemainExcel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox uiRemainWord;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox uiRemainPowerPoint;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.CheckBox uiEnableTimeOut;
        private System.Windows.Forms.CheckBox passwdCheck;
        private System.Windows.Forms.Label fileNameWord;
        private System.Windows.Forms.Label fileNameExcel;
    }
}

