namespace TriviaCS
{
    partial class SignUp
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
            this.username = new System.Windows.Forms.TextBox();
            this.pass = new System.Windows.Forms.TextBox();
            this.mail = new System.Windows.Forms.TextBox();
            this.ok = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.password = new System.Windows.Forms.Label();
            this.email = new System.Windows.Forms.Label();
            this.back = new System.Windows.Forms.Button();
            this.ErrorBox = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // username
            // 
            this.username.Location = new System.Drawing.Point(93, 45);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(211, 20);
            this.username.TabIndex = 0;
            this.username.TextChanged += new System.EventHandler(this.username_TextChanged);
            // 
            // pass
            // 
            this.pass.Location = new System.Drawing.Point(93, 83);
            this.pass.Name = "pass";
            this.pass.Size = new System.Drawing.Size(211, 20);
            this.pass.TabIndex = 1;
            this.pass.TextChanged += new System.EventHandler(this.pass_TextChanged);
            // 
            // mail
            // 
            this.mail.Location = new System.Drawing.Point(93, 119);
            this.mail.Name = "mail";
            this.mail.Size = new System.Drawing.Size(211, 20);
            this.mail.TabIndex = 2;
            this.mail.TextChanged += new System.EventHandler(this.mail_TextChanged);
            // 
            // ok
            // 
            this.ok.Location = new System.Drawing.Point(93, 168);
            this.ok.Name = "ok";
            this.ok.Size = new System.Drawing.Size(96, 50);
            this.ok.TabIndex = 3;
            this.ok.Text = "Sign Up";
            this.ok.UseVisualStyleBackColor = true;
            this.ok.Click += new System.EventHandler(this.ok_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 17);
            this.label1.TabIndex = 4;
            this.label1.Text = "Username:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // password
            // 
            this.password.AutoSize = true;
            this.password.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.password.Location = new System.Drawing.Point(11, 86);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(73, 17);
            this.password.TabIndex = 5;
            this.password.Text = "Password:";
            this.password.Click += new System.EventHandler(this.label2_Click);
            // 
            // email
            // 
            this.email.AutoSize = true;
            this.email.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.email.Location = new System.Drawing.Point(12, 122);
            this.email.Name = "email";
            this.email.Size = new System.Drawing.Size(46, 17);
            this.email.TabIndex = 6;
            this.email.Text = "Email:";
            this.email.Click += new System.EventHandler(this.label3_Click);
            // 
            // back
            // 
            this.back.Location = new System.Drawing.Point(208, 168);
            this.back.Name = "back";
            this.back.Size = new System.Drawing.Size(96, 50);
            this.back.TabIndex = 7;
            this.back.Text = "Back";
            this.back.UseVisualStyleBackColor = true;
            this.back.Click += new System.EventHandler(this.back_Click);
            // 
            // ErrorBox
            // 
            this.ErrorBox.AutoSize = true;
            this.ErrorBox.ForeColor = System.Drawing.Color.Red;
            this.ErrorBox.Location = new System.Drawing.Point(93, 13);
            this.ErrorBox.Name = "ErrorBox";
            this.ErrorBox.Size = new System.Drawing.Size(0, 13);
            this.ErrorBox.TabIndex = 8;
            // 
            // SignUp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(344, 248);
            this.Controls.Add(this.ErrorBox);
            this.Controls.Add(this.back);
            this.Controls.Add(this.email);
            this.Controls.Add(this.password);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ok);
            this.Controls.Add(this.mail);
            this.Controls.Add(this.pass);
            this.Controls.Add(this.username);
            this.Name = "SignUp";
            this.Text = "SignUp";
            this.Load += new System.EventHandler(this.SignUp_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox username;
        private System.Windows.Forms.TextBox pass;
        private System.Windows.Forms.TextBox mail;
        private System.Windows.Forms.Button ok;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label password;
        private System.Windows.Forms.Label email;
        private System.Windows.Forms.Button back;
        private System.Windows.Forms.Label ErrorBox;
    }
}