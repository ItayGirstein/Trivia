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
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(287, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "Room List:";
            // 
            // Refresh
            // 
            this.Refresh.Location = new System.Drawing.Point(170, 327);
            this.Refresh.Name = "Refresh";
            this.Refresh.Size = new System.Drawing.Size(75, 23);
            this.Refresh.TabIndex = 1;
            this.Refresh.Text = "Refresh";
            this.Refresh.UseVisualStyleBackColor = true;
            this.Refresh.Click += new System.EventHandler(this.Refresh_Click);
            // 
            // Back
            // 
            this.Back.Location = new System.Drawing.Point(410, 327);
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
            this.rooms.Location = new System.Drawing.Point(220, 98);
            this.rooms.Name = "rooms";
            this.rooms.Size = new System.Drawing.Size(236, 44);
            this.rooms.TabIndex = 3;
            this.rooms.SelectedIndexChanged += new System.EventHandler(this.rooms_SelectedIndexChanged);
            // 
            // joinButton
            // 
            this.joinButton.Enabled = false;
            this.joinButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.joinButton.Location = new System.Drawing.Point(281, 317);
            this.joinButton.Name = "joinButton";
            this.joinButton.Size = new System.Drawing.Size(94, 39);
            this.joinButton.TabIndex = 4;
            this.joinButton.Text = "JOIN";
            this.joinButton.UseVisualStyleBackColor = true;
            // 
            // JoinRoom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(683, 448);
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
    }
}