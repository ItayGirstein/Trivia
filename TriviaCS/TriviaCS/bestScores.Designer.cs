namespace TriviaCS
{
    partial class bestScores
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
            this.back = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.FirstScore = new System.Windows.Forms.Label();
            this.SecondScore = new System.Windows.Forms.Label();
            this.ThirdScore = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // back
            // 
            this.back.Location = new System.Drawing.Point(56, 250);
            this.back.Name = "back";
            this.back.Size = new System.Drawing.Size(96, 50);
            this.back.TabIndex = 15;
            this.back.Text = "Back";
            this.back.UseVisualStyleBackColor = true;
            this.back.Click += new System.EventHandler(this.back_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 24);
            this.label1.TabIndex = 16;
            this.label1.Text = "Best Scores:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // FirstScore
            // 
            this.FirstScore.AutoSize = true;
            this.FirstScore.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FirstScore.Location = new System.Drawing.Point(52, 74);
            this.FirstScore.Name = "FirstScore";
            this.FirstScore.Size = new System.Drawing.Size(92, 22);
            this.FirstScore.TabIndex = 17;
            this.FirstScore.Text = "FirstScore";
            this.FirstScore.Click += new System.EventHandler(this.label2_Click);
            // 
            // SecondScore
            // 
            this.SecondScore.AutoSize = true;
            this.SecondScore.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SecondScore.Location = new System.Drawing.Point(52, 131);
            this.SecondScore.Name = "SecondScore";
            this.SecondScore.Size = new System.Drawing.Size(118, 22);
            this.SecondScore.TabIndex = 18;
            this.SecondScore.Text = "SecondScore";
            // 
            // ThirdScore
            // 
            this.ThirdScore.AutoSize = true;
            this.ThirdScore.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ThirdScore.Location = new System.Drawing.Point(52, 186);
            this.ThirdScore.Name = "ThirdScore";
            this.ThirdScore.Size = new System.Drawing.Size(99, 22);
            this.ThirdScore.TabIndex = 19;
            this.ThirdScore.Text = "ThirdScore";
            // 
            // bestScores
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(345, 333);
            this.Controls.Add(this.ThirdScore);
            this.Controls.Add(this.SecondScore);
            this.Controls.Add(this.FirstScore);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.back);
            this.Name = "bestScores";
            this.Text = "bestScores";
            this.Load += new System.EventHandler(this.bestScores_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button back;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label FirstScore;
        private System.Windows.Forms.Label SecondScore;
        private System.Windows.Forms.Label ThirdScore;
    }
}