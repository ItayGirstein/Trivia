namespace TriviaCS
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.username = new System.Windows.Forms.TextBox();
            this.password = new System.Windows.Forms.TextBox();
            this.SignIn = new System.Windows.Forms.Button();
            this.SignUp = new System.Windows.Forms.Button();
            this.CreateRoom = new System.Windows.Forms.Button();
            this.JoinRoom = new System.Windows.Forms.Button();
            this.BestScores = new System.Windows.Forms.Button();
            this.MyStatus = new System.Windows.Forms.Button();
            this.Quit = new System.Windows.Forms.Button();
            this.signOut = new System.Windows.Forms.Button();
            this.ErrorBox = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.label1.Location = new System.Drawing.Point(186, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "TRIVYA";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(67, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "USER:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(34, 105);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "PASSWORD:";
            // 
            // username
            // 
            this.username.Location = new System.Drawing.Point(116, 49);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(226, 20);
            this.username.TabIndex = 3;
            this.username.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // password
            // 
            this.password.Location = new System.Drawing.Point(116, 102);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(226, 20);
            this.password.TabIndex = 4;
            // 
            // SignIn
            // 
            this.SignIn.Location = new System.Drawing.Point(109, 143);
            this.SignIn.Name = "SignIn";
            this.SignIn.Size = new System.Drawing.Size(82, 25);
            this.SignIn.TabIndex = 5;
            this.SignIn.Text = "Sign In";
            this.SignIn.UseVisualStyleBackColor = true;
            this.SignIn.Click += new System.EventHandler(this.button1_Click);
            // 
            // SignUp
            // 
            this.SignUp.Location = new System.Drawing.Point(244, 142);
            this.SignUp.Name = "SignUp";
            this.SignUp.Size = new System.Drawing.Size(82, 25);
            this.SignUp.TabIndex = 6;
            this.SignUp.Text = "Sign Up";
            this.SignUp.UseVisualStyleBackColor = true;
            this.SignUp.Click += new System.EventHandler(this.SignUp_Click);
            // 
            // CreateRoom
            // 
            this.CreateRoom.Enabled = false;
            this.CreateRoom.Location = new System.Drawing.Point(244, 181);
            this.CreateRoom.Name = "CreateRoom";
            this.CreateRoom.Size = new System.Drawing.Size(82, 25);
            this.CreateRoom.TabIndex = 8;
            this.CreateRoom.Text = "Create Room";
            this.CreateRoom.UseVisualStyleBackColor = true;
            this.CreateRoom.Click += new System.EventHandler(this.CreateRoom_Click);
            // 
            // JoinRoom
            // 
            this.JoinRoom.Enabled = false;
            this.JoinRoom.Location = new System.Drawing.Point(109, 182);
            this.JoinRoom.Name = "JoinRoom";
            this.JoinRoom.Size = new System.Drawing.Size(82, 25);
            this.JoinRoom.TabIndex = 7;
            this.JoinRoom.Text = "Join Room";
            this.JoinRoom.UseVisualStyleBackColor = true;
            this.JoinRoom.Click += new System.EventHandler(this.JoinRoom_Click);
            // 
            // BestScores
            // 
            this.BestScores.Enabled = false;
            this.BestScores.Location = new System.Drawing.Point(244, 219);
            this.BestScores.Name = "BestScores";
            this.BestScores.Size = new System.Drawing.Size(82, 25);
            this.BestScores.TabIndex = 10;
            this.BestScores.Text = "Best Scores";
            this.BestScores.UseVisualStyleBackColor = true;
            this.BestScores.Click += new System.EventHandler(this.BestScores_Click);
            // 
            // MyStatus
            // 
            this.MyStatus.Enabled = false;
            this.MyStatus.Location = new System.Drawing.Point(109, 220);
            this.MyStatus.Name = "MyStatus";
            this.MyStatus.Size = new System.Drawing.Size(82, 25);
            this.MyStatus.TabIndex = 9;
            this.MyStatus.Text = "My Status";
            this.MyStatus.UseVisualStyleBackColor = true;
            this.MyStatus.Click += new System.EventHandler(this.MyStatus_Click);
            // 
            // Quit
            // 
            this.Quit.Location = new System.Drawing.Point(178, 273);
            this.Quit.Name = "Quit";
            this.Quit.Size = new System.Drawing.Size(82, 25);
            this.Quit.TabIndex = 11;
            this.Quit.Text = "Quit";
            this.Quit.UseVisualStyleBackColor = true;
            this.Quit.Click += new System.EventHandler(this.Quit_Click);
            // 
            // signOut
            // 
            this.signOut.Enabled = false;
            this.signOut.Location = new System.Drawing.Point(178, 142);
            this.signOut.Name = "signOut";
            this.signOut.Size = new System.Drawing.Size(82, 25);
            this.signOut.TabIndex = 12;
            this.signOut.Text = "Sign Out";
            this.signOut.UseVisualStyleBackColor = true;
            this.signOut.Visible = false;
            this.signOut.Click += new System.EventHandler(this.signOut_Click);
            // 
            // ErrorBox
            // 
            this.ErrorBox.AutoSize = true;
            this.ErrorBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ErrorBox.ForeColor = System.Drawing.Color.Red;
            this.ErrorBox.Location = new System.Drawing.Point(197, 72);
            this.ErrorBox.Name = "ErrorBox";
            this.ErrorBox.Size = new System.Drawing.Size(0, 17);
            this.ErrorBox.TabIndex = 13;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(412, 327);
            this.Controls.Add(this.ErrorBox);
            this.Controls.Add(this.signOut);
            this.Controls.Add(this.Quit);
            this.Controls.Add(this.BestScores);
            this.Controls.Add(this.MyStatus);
            this.Controls.Add(this.CreateRoom);
            this.Controls.Add(this.JoinRoom);
            this.Controls.Add(this.SignUp);
            this.Controls.Add(this.SignIn);
            this.Controls.Add(this.password);
            this.Controls.Add(this.username);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox username;
        private System.Windows.Forms.TextBox password;
        private System.Windows.Forms.Button SignIn;
        private System.Windows.Forms.Button SignUp;
        private System.Windows.Forms.Button CreateRoom;
        private System.Windows.Forms.Button JoinRoom;
        private System.Windows.Forms.Button BestScores;
        private System.Windows.Forms.Button MyStatus;
        private System.Windows.Forms.Button Quit;
        private System.Windows.Forms.Button signOut;
        private System.Windows.Forms.Label ErrorBox;
    }
}

