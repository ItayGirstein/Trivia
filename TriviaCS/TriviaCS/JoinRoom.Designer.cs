namespace TriviaCS
{
    partial class JoinRoom
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
            this.Refresh = new System.Windows.Forms.Button();
            this.Back = new System.Windows.Forms.Button();
            this.rooms = new System.Windows.Forms.ListBox();
            this.joinButton = new System.Windows.Forms.Button();
            this.roomUsers_Text = new System.Windows.Forms.Label();
            this.users = new System.Windows.Forms.ListBox();
            this.errorBox = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(191, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "Room List:";
            // 
            // Refresh
            // 
            this.Refresh.Location = new System.Drawing.Point(74, 325);
            this.Refresh.Name = "Refresh";
            this.Refresh.Size = new System.Drawing.Size(75, 23);
            this.Refresh.TabIndex = 1;
            this.Refresh.Text = "Refresh";
            this.Refresh.UseVisualStyleBackColor = true;
            this.Refresh.Click += new System.EventHandler(this.Refresh_Click);
            // 
            // Back
            // 
            this.Back.Location = new System.Drawing.Point(314, 325);
            this.Back.Name = "Back";
            this.Back.Size = new System.Drawing.Size(75, 23);
            this.Back.TabIndex = 2;
            this.Back.Text = "Back";
            this.Back.UseVisualStyleBackColor = true;
            this.Back.Click += new System.EventHandler(this.Back_Click);
            // 
            // rooms
            // 
            this.rooms.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rooms.FormattingEnabled = true;
            this.rooms.ItemHeight = 20;
            this.rooms.Items.AddRange(new object[] {
            "dasdasdas",
            "dasdasdasd",
            "asdasdassd",
            "daaa"});
            this.rooms.Location = new System.Drawing.Point(124, 96);
            this.rooms.Name = "rooms";
            this.rooms.Size = new System.Drawing.Size(236, 44);
            this.rooms.TabIndex = 3;
            this.rooms.SelectedIndexChanged += new System.EventHandler(this.rooms_SelectedIndexChanged);
            // 
            // joinButton
            // 
            this.joinButton.Enabled = false;
            this.joinButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.joinButton.Location = new System.Drawing.Point(185, 315);
            this.joinButton.Name = "joinButton";
            this.joinButton.Size = new System.Drawing.Size(94, 39);
            this.joinButton.TabIndex = 4;
            this.joinButton.Text = "JOIN";
            this.joinButton.UseVisualStyleBackColor = true;
            // 
            // roomUsers_Text
            // 
            this.roomUsers_Text.AutoSize = true;
            this.roomUsers_Text.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.roomUsers_Text.Location = new System.Drawing.Point(167, 158);
            this.roomUsers_Text.Name = "roomUsers_Text";
            this.roomUsers_Text.Size = new System.Drawing.Size(144, 24);
            this.roomUsers_Text.TabIndex = 5;
            this.roomUsers_Text.Text = "Room\'s players:";
            this.roomUsers_Text.Visible = false;
            // 
            // users
            // 
            this.users.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.users.FormattingEnabled = true;
            this.users.ItemHeight = 20;
            this.users.Items.AddRange(new object[] {
            "dasdasdas",
            "dasdasdasd",
            "asdasdassd",
            "daaa"});
            this.users.Location = new System.Drawing.Point(127, 200);
            this.users.Name = "users";
            this.users.Size = new System.Drawing.Size(236, 44);
            this.users.TabIndex = 6;
            this.users.Visible = false;
            // 
            // errorBox
            // 
            this.errorBox.AutoSize = true;
            this.errorBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.errorBox.ForeColor = System.Drawing.Color.Red;
            this.errorBox.Location = new System.Drawing.Point(217, 267);
            this.errorBox.Name = "errorBox";
            this.errorBox.Size = new System.Drawing.Size(0, 18);
            this.errorBox.TabIndex = 7;
            // 
            // JoinRoom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(478, 448);
            this.Controls.Add(this.errorBox);
            this.Controls.Add(this.users);
            this.Controls.Add(this.roomUsers_Text);
            this.Controls.Add(this.joinButton);
            this.Controls.Add(this.rooms);
            this.Controls.Add(this.Back);
            this.Controls.Add(this.Refresh);
            this.Controls.Add(this.label1);
            this.Name = "JoinRoom";
            this.Text = "JoinRoom";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Refresh;
        private System.Windows.Forms.Button Back;
        private System.Windows.Forms.ListBox rooms;
        private System.Windows.Forms.Button joinButton;
        private System.Windows.Forms.Label roomUsers_Text;
        private System.Windows.Forms.ListBox users;
        private System.Windows.Forms.Label errorBox;
    }
}